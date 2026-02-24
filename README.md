_This project has been created as part of the 42 curriculum by alicuza._

# fdf — fil de fer

## Description

fdf is a wireframe renderer for height maps, written in C using MiniLibX (Linux/X11).
Points on a 2D grid are lifted into 3D space by their z-values, connected by edges,
and projected onto the screen with real-time rotation, translation, and zoom.

---

## Table of Contents

- [Description](#description)
- [Controls](#controls)
- [Instructions](#instructions)
  - [Compilation](#compilation)
  - [Usage](#usage)
  - [Map Format](#map-format)
- [Known Limitations](#known-limitations)
- [Algorithm and Data Structure](#algorithm-and-data-structure)
  - [Architecture Overview](#architecture-overview)
  - [Core Data Structure](#core-data-structure)
  - [Parsing and Model Initialization](#parsing-and-model-initialization)
  - [Math](#math)
    - [Quaternions](#quaternions)
    - [Rotation Matrix from Quaternion](#rotation-matrix-from-quaternion)
    - [Transform, Rotate, Scale — TRS Matrix](#transform-rotate-scale--trs-matrix)
    - [Projections](#projections)
    - [Vector and Array Normalization](#vector-and-array-normalization)
  - [The Render Loop](#the-render-loop)
  - [User Input Handling](#user-input-handling)
  - [Line Drawing — `Bresenham's Algorithm`](#line-drawing--bresenhams-algorithm)
  - [Color](#color)
  - [Error Handling and Cleanup](#error-handling-and-cleanup)
- [Build](#build)
- [MLX](#mlx)
  - [Behaviour](#behaviour)
  - [X11 Events](#x11-events)
  - [Relevant Event Type and Mask Codes](#relevant-event-type-and-mask-codes)
  - [Keysyms](#keysyms)
- [Resources](#resources)
  - [Documentation and References](#documentation-and-references)
  - [AI Usage](#ai-usage)

---

## Controls

```
General
─────────────────────────────────────────────────
 ESC          quit
 Y            reset transform
 R            toggle auto-rotation
 C            cycle projection (Isometric ↔ 2:1 Dimetric)

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
 - =          zoom in / out
─────────────────────────────────────────────────
```

---

## Instructions

### Compilation

Compile the project by running one of the following `make` commands:

- `make` or `make all` - Compiles `fdf`;
- `make clean` - Removes object and dependency files;
- `make fclean` - Additionally removes the binary and the libs;
- `make re` - Recompiles the entire project from scratch;
- `make debug` - Compiles with the -g flag for debugging;

### Usage

Run the program with a map file:

```bash
./fdf path/to/map.fdf
```

---

### Map Format

- plain text
- whitespace-separated **integers**
- one row per line
- **all rows must have the same width**
- positive values are peaks, negative values are valleys

Example:

```text
0 0 0 0 0
0 1 2 1 0
0 2 8 2 0
0 1 2 1 0
0 0 0 0 0
```

---

## Known Limitations

- **Parsing:** only whitespace-separated integers are supported (no `z,color` tokens).
- **Clipping:** a full line clipping algorithm is not implemented yet.
				Edges are skipped only if both endpoints are fully off-screen on the same side,
				and partially visible edges rely on a per-pixel bounds guard.
- **Color:** currently fixed to `0x00FFFFFF` (white).
- **Rotation controls:** incremental rotations are applied in world axes (see quaternion section),
						 which makes movement appear diagonal from the viewer perspective.

---

## Algorithm and Data Structure

### Architecture Overview

The entire mutable program state lives in a single `t_state_data` struct that
is passed by pointer almost everywhere. This avoids global variables and provides
a single place to track and clean up every resource.

```
t_state_data
├── t_img_data			img		- MiniLibX image buffer
├── t_win_data			win		- window handle + dimensions
├── t_map_data			map		- grid width × height, total point count
├── t_pnt_data			p
│   ├── t_fvec3d_arr	model	- centered, normalized model-space coords
│   ├── t_fvec3d_arr	world	- after TRS transform
│   └── t_vec2d_arr		screen	- integer pixel coords after projection
├── t_trans_data		trans	- quaternion rotation, offset, scale, autorot
├── t_proj				proj	- current projection enum
├── int[CMD_CNT]		key		- live key-state bitmask
├── void*				mlx_ptr
└── …fd, path, gnl_line, split_line (all tracked for safe cleanup)
```

Points are stored using **Structure of Arrays (SoA)** rather than an
**Array of Structs (AoS)**, keeping each coordinate component contiguous in memory.
This is cache-friendly for the tight loops that transform every point each frame.

---

### Core Data Structure

The key struct is the state container:

```c
typedef struct s_state_data
{
	// MiniLibX
	t_img_data		img;
	t_win_data		win;

	// Map and points
	t_map_data		map;
	t_pnt_data		p;

	// Transform and projection
	t_trans_data	trans;
	t_proj			proj;

	// Input
	int				key[CMD_CNT];

	// Tracked resources for safe cleanup
	void			*mlx_ptr;
	int				fd;
	char			*path;
	char			*gnl_line;
	char			**split_line;
}	t_state_data;
```

---

### Parsing and Model Initialization

Initialization happens in two passes over the file so that memory only needs
to be allocated once.

1. **Pass 1 — `get_map_dim`**
- reads every line with `get_next_line`
- splits on whitespace
- counts valid numeric tokens per row and the total number of rows
- verifies all rows share the same width (mismatch is a fatal error)

2. **Pass 2 — `init_model`**
- allocates six `double` arrays (model x/y/z, world x/y/z) and
  two `int` arrays (screen x/y), all of length `map.size`
- reads the file again and converts tokens with `ft_atoi`
- assigns grid coordinates directly:

```c
model.x[i + row * width] = (double)column;
model.y[i + row * width] = (double)row;
model.z[i + row * width] = (double)parsed_value;
```

After parsing, `center_norm_model` is called:

- the model is centered at the origin by subtracting a centroid.
  (`x` & `y` use grid midpoints, `z` uses the midpoint of `min` and `max z`)
- `vec_soa_norm` divides every coordinate by a single global magnitude so the
  model fits a consistent unit bound.

This makes the initial scale setting (`0.5 * min(window width, window height)`)
produce predictable results across maps.

---

### Math

#### Quaternions

Quaternions represent orientation because they compose cleanly, avoid gimbal lock,
and convert directly to a rotation matrix.

A quaternion is $q = (w, x, y, z)$ where $w$ is the scalar component and
$(x, y, z)$ is the vector component.

Quaternion multiplication is:

$$
q_1 q_2 =
\left(
w_1w_2 - x_1x_2 - y_1y_2 - z_1z_2,\;
w_1x_2 + x_1w_2 + y_1z_2 - z_1y_2,\;
w_1y_2 - x_1z_2 + y_1w_2 + z_1x_2,\;
w_1z_2 + x_1y_2 - y_1x_2 + z_1w_2
\right).
$$

Multiplication is non-commutative: $q_1q_2 \ne q_2q_1$.

In this project, incremental rotations are multiplied on the **left**
of the accumulated rotation:

```c
state->trans.rot = quat_norm(quat_mult(quat_from_aa(ROT_SPEED, axis),
				       state->trans.rot));
```

This applies rotations around **fixed world axes**. The model moves correctly
along the axes, but the viewer sees it moving diagonally, because the usual
movement controls assume a perspective from inside the world, not from outside.

**Axis-angle to quaternion**
Rotate by angle $\theta$ around unit axis $\hat{\mathbf{n}}$:

$$
q = \left(\cos\frac{\theta}{2},\; \hat{\mathbf{n}} \sin\frac{\theta}{2}\right).
$$

**Normalization**
To prevent floating point drift:

$$
\lVert q \rVert = \sqrt{w^2 + x^2 + y^2 + z^2}, \qquad \hat{q} = \frac{q}{\lVert q \rVert}.
$$

**Planned improvement**
For user input, the incremental rotation always uses the same constant `delta_angle`
and one of the 6 unit axes ($\pm x$, $\pm y$, $\pm z$). This means the corresponding
quaternions do not need to be recomputed every frame: a precomputed quaternion for
each direction can be stored once and then reused in the render loop.

---

#### Rotation Matrix from Quaternion

A unit quaternion $q = (w, x, y, z)$ expands to:

$$
R =
\begin{bmatrix}
1 - 2(y^2 + z^2) & 2(xy - zw)       & 2(xz + yw) \\
2(xy + zw)       & 1 - 2(x^2 + z^2) & 2(yz - xw) \\
2(xz - yw)       & 2(yz + xw)       & 1 - 2(x^2 + y^2)
\end{bmatrix}.
$$

No trig calls are needed at render time: `sin`/`cos` happen in `quat_from_aa`,
and the matrix is built from products of stored components.

---

#### Transform, Rotate, Scale — TRS Matrix

Model-to-world is a single $4 \times 4$ matrix combining rotation,
uniform scale, and translation:

$$
\mathrm{TRS} =
\begin{bmatrix}
R s & \mathbf{t} \\
\mathbf{0}^T & 1
\end{bmatrix}.
$$

In the tight SoA loop, translation is added as an offset:

```c
p1->x[i] = p0->x[i]*m.pos[0]  + p0->y[i]*m.pos[1]  + p0->z[i]*m.pos[2]  + m.pos[3];
p1->y[i] = p0->x[i]*m.pos[4]  + p0->y[i]*m.pos[5]  + p0->z[i]*m.pos[6]  + m.pos[7];
p1->z[i] = p0->x[i]*m.pos[8]  + p0->y[i]*m.pos[9]  + p0->z[i]*m.pos[10] + m.pos[11];
```

---

#### Projections

Projection is applied to world coordinates using a $4 \times 4$ projection matrix,
then rounded to integer pixels with a viewport offset so the origin maps to the image center.

**Matrix notation**
This project uses **column-major notation**. That means:
- $x$ is the **column number**
- $y$ denotes the **row number**
- a point is a column vector and is transformed as $\mathbf{s} = P\mathbf{p}$

A point is treated as a homogeneous vector:

$$
\mathbf{p} = \begin{bmatrix} x \\ y \\ z \\ 1 \end{bmatrix}, \qquad
\mathbf{s} = P \mathbf{p}
$$

and the final 2D pixel coordinates are:

$$
x_{pix} = \mathrm{round}(s_x) + \frac{w_{win}}{2}, \qquad
y_{pix} = \mathrm{round}(s_y) + \frac{h_{win}}{2}.
$$

The projection matrix is kept as $4 \times 4$ to reuse the same matrix-vector
multiplication path as TRS, even though only the first two rows are used for
screen-space coordinates.

**Isometric**

$$
P_{iso} =
\begin{bmatrix}
\sqrt{\frac12} & -\sqrt{\frac12} & 0 & 0 \\
\sqrt{\frac16} & \sqrt{\frac16} & -\sqrt{\frac23} & 0 \\
0 & 0 & 0 & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

$$
x_s = x\sqrt{\frac12} - y\sqrt{\frac12}
$$

$$
y_s = x\sqrt{\frac16} + y\sqrt{\frac16} - z\sqrt{\frac23}
$$

**2:1 Dimetric**

$$
P_{dim} =
\begin{bmatrix}
\frac{\sqrt{3}}{2} & -\frac{\sqrt{3}}{2} & 0 & 0 \\
0.5 & 0.5 & -1.0 & 0 \\
0 & 0 & 0 & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

$$
x_s = x\frac{\sqrt{3}}{2} - y\frac{\sqrt{3}}{2}
$$

$$
y_s = 0.5x + 0.5y - 1.0z
$$

Pressing `c` cycles through the projection enum at runtime.

---

#### Vector and Array Normalization

`vec_norm` normalizes a single vector to unit length
 (and returns a zero vector for near-zero magnitudes).
`vec_soa_norm` normalizes the entire model by dividing all coordinates
 by one global magnitude, preserving the shape while keeping the whole
 model inside a consistent unit bound.

---

### The Render Loop

`mlx_loop_hook` calls `render` on every frame:

```
render()
 ├── apply_zoom()
 ├── apply_translation()
 ├── apply_rotation()
 ├── model_to_world()
 ├── world_to_screen()
 └── draw()
```

Key state is tracked as an integer array indexed by a command enum:
- key press sets `key[cmd] = 1`
- key release clears it

This produces continuous motion while a key is held.

---

### User Input Handling

User input is tracked as a key-state bitmask array indexed by a `t_command` enum.
This avoids one-off key callbacks and allows smooth continuous motion by applying
small deltas each frame while a key is held.

```c
typedef enum e_command
{
	MOVE_XP,
	MOVE_XN,
	MOVE_YP,
	MOVE_YN,
	MOVE_ZP,
	MOVE_ZN,
	ROT_XP,
	ROT_XN,
	ROT_YP,
	ROT_YN,
	ROT_ZP,
	ROT_ZN,
	ZOOM_IN,
	ZOOM_OUT,
	CMD_CNT,
}	t_command;
```

Event handlers only update the state and then the render loop modifies the corresponding
values in the transformation struct, subsequently used to compute the TRS matrix.

#### Key to command mapping (makeshift lookup table)

The key press/release hooks receive a keysym (from `<X11/keysym.h>`).
In order to use a stable indexing scheme, keysyms are mapped to commands
through a small lookup table.

Conceptually:

```c
typedef struct s_keymap
{
	int			keysym;
	t_command		cmd;
}	t_keymap;

/*
	{XK_w, MOVE_YP}, {XK_s, MOVE_YN}, ...
*/

t_command	keysym_to_cmd(int keysym);
```

The press/release handlers do:

- `cmd = keysym_to_cmd(keysym)`
- if `cmd` is valid: `state->key[cmd] = 1` on press, `0` on release
- if the keysym is not mapped: it is ignored (a sentinel value `CMD_CNT`)

#### Continuous input in the render loop

Each frame reads the key array and applies small increments:

- translation: adds/subtracts a constant to `trans.offset`
- rotation: composes a new incremental quaternion
- zoom: multiplies/divides `trans.scale`

This keeps the behaviour consistent across all commands, and avoids having long
`if (keysym == ...)` chains inside the frame loop.

Toggle commands (projection cycling, autorotation) are handled as edge-triggered
events inside the key press handler to avoid repeats.

---

### Line Drawing — `Bresenham's Algorithm`

Standard Bresenham with sign-aware accumulator:
- if $|\Delta x| \ge |\Delta y|$
	- the x-coordinate iterates through the loop (`draw_hline`)
	- otherwise y iterates through it (`draw_vline`)

All arithmetic stays in integers, which is the biggest advantage.

**Clipping**
A full clipping algorithm is not implemented. Instead:
- edges with both endpoints fully off-screen on the same side are skipped
- partially visible edges are rasterized with a per-pixel bounds guard

This prevents out-of-bounds writes while keeping the implementation small.
I am planning on implementing the `Liang–Barsky line-clipping algorithm`
at a future date.

---

### Color

Color is currently fixed at `0x00FFFFFF` (white) for all pixels.

---

### Error Handling and Cleanup

`handle_exit` is the single exit point for both normal and error paths:
- destroys MiniLibX resources
- frees all point arrays
- closes the fd if open
- frees `get_next_line` buffers and split arrays
- flushes `get_next_line` static storage via `get_next_line(-255)`
- prints errors via `perror(caller)` on failure
- exits with the given status code

Every allocation and the opened fd are tracked in `t_state_data`,
so cleanup is safe even on partial initialization.

---

## Build

```bash
make        # build fdf
make clean  # remove object files
make fclean # remove object files and binary
make re     # fclean + make
make debug  # build with -g flag
```

**Dependencies**
- MiniLibX (Linux, X11)
- libft (bundled)
- `-lm`, `-lX11`, `-lXext`

---

## MLX

- is a wrapper for the X11 and Xext API

### Behaviour

- not documented properly in the man pages:
	- the `mlx_ptr` needs to be freed.
	- the hook needed for closing the display by clicking on the x is
	  `mlx_hook`, a generic hook, which takes X11 Event(Type)s and Masks.
	- the window close button sends a `DestroyNotify (17)` event.
	  handling it requires registering a hook such as
	  `mlx_hook(win, DestroyNotify, StructureNotifyMask, ...)`.

---

### X11 Events

The common Types are bold and have the corresponding code in brackets:

| Event Category | Event Type (Codes) |
| :-- | :-- |
| Keyboard Events | **KeyPress (2)**, **KeyRelease (3)** |
| Pointer events | **ButtonPress (4)**, **ButtonRelease (5)**, **MotionNotify (6)** |
| Exposure events | **Expose (12)** |
| Window state notification events | DestroyNotify, ConfigureNotify, MapNotify, UnmapNotify |
| **Client communication events** | **ClientMessage (33)** |

### Relevant Event Type and Mask Codes

Taken from `/usr/include/X11/X.h`

```c
#define KeyPressMask			(1L<<0)
#define KeyReleaseMask			(1L<<1)
#define StructureNotifyMask		(1L<<17)

#define KeyPress				2
#define KeyRelease				3
#define DestroyNotify			17
#define ClientMessage			33
```

### Keysyms

Full list in `/usr/include/X11/keysymdef.h`

Headers used:
- `<X11/X.h>`
- `<X11/keysym.h>`

Some keysyms used in this project:

```c
#define XK_Escape		0xff1b

#define XK_minus		0x002d
#define XK_equal		0x003d

#define XK_w			0x0077
#define XK_a			0x0061
#define XK_s			0x0073
#define XK_d			0x0064
#define XK_q			0x0071
#define XK_e			0x0065
```

---

## Resources

### Documentation and References

- [World, View, Projection matrices](https://www.codinglabs.net/article_world_view_projection_matrix.aspx) - world/view/projection decomposition and matrix multiplication order;
- [Understanding Quaternions](https://www.3dgep.com/understanding-quaternions/) - quaternion intuition, axis-angle conversion, and rotation matrices;
- [Quaternions (gltut, Tut08)](https://paroj.github.io/gltut/Positioning/Tut08%20Quaternions.html) - quaternion derivations and practical usage patterns;
- [Memory Layout Transformations (AoS vs SoA)](https://www.intel.com/content/www/us/en/developer/articles/technical/memory-layout-transformations.html) - why SoA is useful for large sequential transform loops;
- [Bresenham's line algorithm](https://www.geeksforgeeks.org/dsa/bresenhams-line-generation-algorithm/) - integer line rasterization;
- [MiniLibX](https://github.com/42Paris/minilibx-linux) - MLX implementation sources (necessary when man pages are incomplete);

**X11**
- [Xlib Programming Manual](https://tronche.com/gui/x/xlib/events/) - reference for Xlib events and masks (useful when using `mlx_hook`);
- [X11 keysyms](https://www.cl.cam.ac.uk/~mgk25/ucs/keysyms.txt) - overview of keysyms and their values;

**Other useful references**
- [Liang–Barsky line clipping](https://en.wikipedia.org/wiki/Liang%E2%80%93Barsky_algorithm) - planned rectangle line clipping algorithm;

### AI Usage

AI tools were used in the following ways during this project:
- brainstorming how to structure documentation and explain math clearly;
- clarifying projection math and quaternion identities;
- drafting and refactoring README text;
