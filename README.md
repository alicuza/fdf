# fdf — fil de fer

A wireframe renderer for height maps, written in C using MiniLibX.  
Points on a 2D grid are lifted into 3D space by their z-values, connected by edges, and projected onto the screen with real-time rotation, translation, and zoom.

> **Screenshot / demo**
>
> Add an image or GIF here:
>
> `![fdf demo](docs/demo.png)`

---

## Features

- Wireframe rendering of grid-based height maps
- Real-time controls: rotation, translation, zoom
- Quaternion orientation (stable composition, no gimbal lock)
- Two projections (live toggle):
  - Isometric
  - 2:1 dimetric (game-art style)
- Cache-friendly point storage (Structure of Arrays / SoA)
- Two-pass parsing (compute dimensions → allocate once → load)
- Bresenham line drawing with safe bounds checks
- Centralized cleanup/error handling via a single exit path

**Planned / Ideas**
- z-based color gradient
- per-pixel color interpolation along edges
- proper line clipping (Cohen–Sutherland / Liang–Barsky)

---

## Quick start (Linux)

### Requirements
- C compiler (clang or gcc) + `make`
- MiniLibX for Linux (X11)
- X11 development libs: `libX11` and `libXext` (package names vary by distro)
- Math library (`-lm`)

### Build
```bash
make
```

### Run
```bash
./fdf path/to/map.fdf
```

---

## Controls

**Notes**
- Most controls are **hold**-to-apply every frame.
- Toggles/resets are **press** once.

```
General
─────────────────────────────────────────────────
 ESC          quit
 Y            reset transform (press)
 R            toggle auto-rotation (press)
 C            cycle projection (press)
             Isometric ↔ 2:1 Dimetric

Translation (hold)
─────────────────────────────────────────────────
 W A S D      translate X/Y
 Q E          translate Z

Rotation (hold)
─────────────────────────────────────────────────
 I K          rotate around Y
 U O          rotate around X
 J L          rotate around Z

Scale (hold)
─────────────────────────────────────────────────
 + -          zoom in / out
─────────────────────────────────────────────────
```

---

## Map format

- Plain text
- Whitespace-separated **integers**
- One row per line
- **All rows must have the same width**
- Positive values are peaks, negative values are valleys

Example:
```text
0 0 0 0 0
0 1 2 1 0
0 2 8 2 0
0 1 2 1 0
0 0 0 0 0
```

---

## Table of Contents

1. [Architecture](#architecture)
2. [Parsing & Model Initialization](#parsing--model-initialization)
3. [Math](#math)
   - [Quaternions](#quaternions)
   - [Rotation Matrix from Quaternion](#rotation-matrix-from-quaternion)
   - [Transform, Rotate, Scale — TRS Matrix](#transform-rotate-scale--trs-matrix)
   - [Projections](#projections)
   - [Vector & Array Normalization](#vector--array-normalization)
4. [The Render Loop](#the-render-loop)
5. [Line Drawing — Bresenham's Algorithm](#line-drawing--bresenhams-algorithm)
6. [Colors](#colors)
7. [Error Handling & Cleanup](#error-handling--cleanup)
8. [Build](#build)

---

## Architecture

The entire mutable program state lives in a single `t_state_data` struct that is passed by pointer almost everywhere.
This sidesteps the need for global variables and gives one obvious place to look when anything goes wrong.

```
t_state_data
├��─ t_img_data   img        — MiniLibX image buffer
├── t_win_data   win        — window handle + dimensions
├── t_map_data   map        — grid width × height, total point count
├── t_pnt_data   p
│   ├── t_fvec3d_arr  model  — centred, normalised model-space coords
│   ├── t_fvec3d_arr  world  — after TRS transform
│   └── t_vec2d_arr   screen — integer pixel coords after projection
├── t_trans_data trans       — quaternion rotation, offset, scale, autorot
├── t_proj       proj        — current projection enum
├── int[CMD_CNT] key         — live key-state bitmask
├── void*        mlx_ptr
└── …fd, path, gnl_line, split_line (all tracked for safe cleanup)
```

Points are stored as three separate arrays (Structure of Arrays, SoA) rather than an array of structs.
This layout keeps each coordinate component contiguous in memory, which is friendlier for the sequential transform loops that touch every element.

**Coordinate spaces**
- **Model space:** parsed grid coordinates, then centered + normalized
- **World space:** after TRS (rotation + uniform scale + translation)
- **Screen space:** after projection + viewport offset to image center

---

## Parsing & Model Initialization

Initialization happens in two passes over the file so that memory only needs to be allocated once.

**Pass 1 — `get_map_dim`**  
Reads every line with `get_next_line`, splits on spaces, and counts valid numeric tokens per row and the total number of rows.
Every row must have the same width; a mismatch is a fatal error.
The product $w \times h$ is stored as `map.size` and used for all allocations.

**Pass 2 — `init_model`**  
Allocates six `double` arrays (model x/y/z, world x/y/z) and two `int` arrays (screen x/y) each of length `map.size`.
Then reads the file again line by line, splitting each row and converting tokens with `ft_atoi`.
Grid coordinates are assigned directly:

```c
model.x[i + row * width] = (double)column;
model.y[i + row * width] = (double)row;
model.z[i + row * width] = (double)parsed_value;
```

After parsing, `center_norm_model` is called:

- The centroid is subtracted from every point so the model is centred at the origin.
  - $x$ and $y$ use grid midpoints.
  - $z$ uses the midpoint of $\min(z)$ and $\max(z)$.
- `vec_soa_norm` divides every coordinate by a single global magnitude so the model fits in a unit bound.
  This makes the initial scale setting ($0.5 \cdot \min(\text{win\_w}, \text{win\_h})$) produce a predictably sized image.

---

## Math

### Quaternions

Quaternions represent orientation because they compose cleanly (no gimbal lock), are cheap to normalize, and convert directly to a rotation matrix.

A quaternion is $q = (w, x, y, z)$ where $w$ is the scalar part and $(x, y, z)$ is the vector part.  
Using the basis identities $i^2 = j^2 = k^2 = ijk = -1$, quaternion multiplication is:

$$
q_1 q_2 =
\left(
w_1w_2 - x_1x_2 - y_1y_2 - z_1z_2,\;
w_1x_2 + x_1w_2 + y_1z_2 - z_1y_2,\;
w_1y_2 - x_1z_2 + y_1w_2 + z_1x_2,\;
w_1z_2 + x_1y_2 - y_1x_2 + z_1w_2
\right).
$$

Quaternion multiplication is non-commutative: $q_1q_2 \ne q_2q_1$.

In this project the new incremental rotation is multiplied on the **left** of the accumulated rotation:

```c
state->trans.rot = quat_norm(quat_mult(quat_from_aa(ROT_SPEED, axis),
                                       state->trans.rot));
```

This applies controls around **fixed world axes** (camera-like), which keeps keybindings intuitive.

**Axis-angle → quaternion**  
To rotate by angle $\theta$ around unit axis $\hat{\mathbf{n}}$:

$$
q = \left(\cos\frac{\theta}{2},\; \hat{\mathbf{n}} \sin\frac{\theta}{2}\right).
$$

```c
t_quat quat_from_aa(double rad, t_fvec3d axis)
{
    axis = vec_norm(axis);
    double s = sin(rad / 2.0);
    return (t_quat){ cos(rad / 2.0), axis.x * s, axis.y * s, axis.z * s };
}
```

**Normalization**  
To prevent floating-point drift, the quaternion is renormalized after each composition.

$$
\lVert q \rVert = \sqrt{w^2 + x^2 + y^2 + z^2}, \qquad \hat{q} = \frac{q}{\lVert q \rVert}.
$$

A unit quaternion encodes a pure rotation (no scaling).

---

### Rotation Matrix from Quaternion

A unit quaternion $q = (w, x, y, z)$ expands to the following $3 \times 3$ rotation matrix:

$$
R =
\begin{bmatrix}
1 - 2(y^2 + z^2) & 2(xy - zw)       & 2(xz + yw) \\
2(xy + zw)       & 1 - 2(x^2 + z^2) & 2(yz - xw) \\
2(xz - yw)       & 2(yz + xw)       & 1 - 2(x^2 + y^2)
\end{bmatrix}.
$$

No trigonometric calls are needed during rendering: $\sin$/$\cos$ are computed once in `quat_from_aa`, then $R$ is built from products of stored components.

---

### Transform, Rotate, Scale — TRS Matrix

Model-to-world combines rotation, **uniform scale**, and translation in a single $4 \times 4$ matrix:

$$
\mathrm{TRS} =
\begin{bmatrix}
R s & \mathbf{t} \\
\mathbf{0}^T & 1
\end{bmatrix}.
$$

Applying it to a point $(x, y, z)$ in homogeneous coordinates:

$$
\begin{bmatrix}
x' \\ y' \\ z' \\ 1
\end{bmatrix}
=
\mathrm{TRS}
\begin{bmatrix}
x \\ y \\ z \\ 1
\end{bmatrix}.
$$

The inner loop in `p_soa_trs_mult_3d` avoids building the homogeneous coordinate explicitly and treats the translation column as an additive offset:

```c
p1->x[i] = p0->x[i]*m.pos[0]  + p0->y[i]*m.pos[1]  + p0->z[i]*m.pos[2]  + m.pos[3];
p1->y[i] = p0->x[i]*m.pos[4]  + p0->y[i]*m.pos[5]  + p0->z[i]*m.pos[6]  + m.pos[7];
p1->z[i] = p0->x[i]*m.pos[8]  + p0->y[i]*m.pos[9]  + p0->z[i]*m.pos[10] + m.pos[11];
```

The matrix is stored in row-major order: element `[i + 4*j]` is row $j$, column $i$.

---

### Projections

Both projections are applied as linear maps from world space to screen space, then pixel coordinates are computed via `round()` and a viewport offset so $(0,0)$ maps to the image center.

**Isometric**

True isometric projection views the scene along $(1,1,1)$. One convenient orthonormal basis is:

$$
\mathbf{r} = \left(\sqrt{\frac12}, -\sqrt{\frac12}, 0\right), \qquad
\mathbf{u} = \left(\sqrt{\frac16}, \sqrt{\frac16}, -\sqrt{\frac23}\right).
$$

Then:

$$
x_s = x\sqrt{\frac12} - y\sqrt{\frac12},
$$
$$
y_s = x\sqrt{\frac16} + y\sqrt{\frac16} - z\sqrt{\frac23}.
$$

**2:1 Dimetric**

A common game-art approximation where horizontal lines slope at 1:2 pixels:

$$
x_s = x\frac{\sqrt{3}}{2} - y\frac{\sqrt{3}}{2},
$$
$$
y_s = 0.5x + 0.5y - 1.0z.
$$

Switching projection is live: pressing **C** cycles the enum; the next `render` rebuilds screen coordinates using the new transform.

---

### Vector & Array Normalization

`vec_norm` normalizes a single vector $\mathbf{v}$:

$$
\hat{\mathbf{v}} =
\begin{cases}
\mathbf{0}, & \lVert \mathbf{v} \rVert \le \varepsilon \\
\frac{\mathbf{v}}{\lVert \mathbf{v} \rVert}, & \text{otherwise}
\end{cases}
$$

and is used to sanitize rotation axes before computing `quat_from_aa`.

`vec_soa_norm` operates on the entire model at parse time by dividing all coordinates by one global magnitude, preserving shape while guaranteeing the entire model fits a consistent bound.

---

## The Render Loop

`mlx_loop_hook` calls `render` on every frame. The call order is:

```
render()
 ├── apply_zoom()         — multiply scale by ZOOM_SPEED if key held
 ├── apply_translation()  — increment offset vector
 ├── apply_rotation()     — compose new incremental quat into trans.rot
 ├── model_to_world()     — build TRS matrix, transform all model points
 ├── world_to_screen()    — apply projection, round to int pixels
 └── draw()               — Bresenham lines + blit image to window
```

Key state is tracked as an integer array indexed by the `t_command` enum.
`handle_key_press` sets `key[cmd] = 1` and `handle_key_release` clears it, so holding a key down produces continuous incremental changes every frame rather than a single step.

---

## Line Drawing — Bresenham's Algorithm

Standard Bresenham with a sign-aware accumulator. The steeper axis drives the loop; the shallower axis is advanced when the accumulated error exceeds a threshold.

Decision between x-driven and y-driven loops:

```c
if (|Δx| >= |Δy|)  draw_hline(...)
else               draw_vline(...)
```

Inside `draw_hline`:

```c
while (i < |Δx|)
{
    put_pixel(x, y, color);
    x += sign.x;
    acc += 2 * |Δy|;
    if (acc > |Δx|)
    {
        y += sign.y;
        acc -= 2 * |Δx|;
    }
}
```

All arithmetic stays in integers (no division, no floats).

**Clipping / bounds safety**
- Coarse rejection via `both_off_screen` (skip lines fully outside on one side)
- Per-pixel `is_on_screen` guard for partially visible lines

---

## Colors

Color is currently fixed at `0x00FFFFFF` (white) for all pixels.

**Planned: z-based gradient**

`get_color(double z)` receives model-space $z$ normalized to $[-1, 1]$. Remap and lerp:

$$
t = \frac{z + 1}{2} \in [0,1]
$$

$$
\mathbf{c}(t) = \mathbf{c}_{low} + t(\mathbf{c}_{high} - \mathbf{c}_{low})
$$

Then pack to `0xRRGGBB`.

**Planned: per-pixel interpolation**

In Bresenham, an approximate parametric position is already available as $t \approx i/|\Delta x|$ (or $i/|\Delta y|$), so:

$$
z(t) = z_0 + t(z_1 - z_0)
$$

and `get_color(z(t))` can be evaluated per pixel.

---

## Error Handling & Cleanup

`handle_exit` is the single exit point for both normal and error paths:

```c
void handle_exit(t_state_data *state, int exit_status, const char *caller)
{
    // destroy MiniLibX resources in order
    // free all point arrays
    // close fd if open
    // free gnl_line and split_line
    // flush get_next_line buffer with fd -255
    // perror(caller) on failure
    // exit(exit_status)
}
```

Every heap allocation and open file descriptor is tracked in `t_state_data`.
A zero-initialized state struct means unallocated pointers are `NULL` and the fd starts at `-1`, so cleanup checks are safe.

`get_next_line(-255)` flushes any internal static buffer that `get_next_line` may hold, preventing a leak on early exit mid-parse.

---

## Build

```bash
make        # build fdf
make clean  # remove object files
make fclean # remove object files and binary
make re     # fclean + make
```

**Dependencies**
- MiniLibX (Linux, X11)
- libft (bundled)
- `-lm`, `-lX11`, `-lXext`