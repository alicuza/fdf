# Makefile
- handling different release types, like having a `make debug` command, needs some additional work, like having .dotfiles that track which release type currently exists and handle it without relinking unnecessarily.
- Felix had the idea of using an environment variable instead of the .dotfiles. But how would an env var retain information from the last compilation to know whether it needs to fclean first or not.

# fdf
## Inspiration
[https://github.com/ailopez-o/42Barcelona-FdF](this mofo projects to a globe)

## TODO
- ~~error handling in fucking general.~~ need to write up my solution.
- ~~cleanup function.~~
- ~~go through comments, fix issues, clean up code~~ completely refactor for norm compliance and sane architecture.
- figure out what types your dimensions need to use, `int`, `unsigned int` and then maybe the types from `stdint.h`
- write README-
- continue with math writeup.
- write transformation function.
- write projection function.

## Math
### Matrices

**multiplication**:

for $A \times B = C$, $c_{ij} = \sum_{k=1}^{n} a_{ik} b_{kj}$

### Quaternions
$i^2 = j^2 = k^2 = -1$

$ij = k$, $jk = i$, $ki = j$

$ji = -k$, $kj = -i$, $ik = -j$

$\begin{array}{c|cccc}
\times & 1 & i & j & k \\
\hline
1 & 1 & i & j & k \\
i & i & -1 & k & -j \\
j & j & -k & -1 & i \\
k & k & j & -i & -1 \\
\end{array}$

for $p$ and $q$, where

$p = a \cdot w + b \cdot i + c \cdot j + d \cdot k$

$q = e \cdot w + f \cdot i + g \cdot j + h \cdot k$

**multiplication**:

$p \cdot q = (a \cdot e - b \cdot f - c \cdot g - d \cdot h) \cdot w$

$\hphantom{p \cdot q }+ (a \cdot f + b \cdot e + c \cdot h - d \cdot g) \cdot i$

$\hphantom{p \cdot q }+ (a \cdot g - b \cdot h + c \cdot e + d \cdot f) \cdot j$

$\hphantom{p \cdot q }+ (a \cdot h + b \cdot g - c \cdot f + d \cdot e) \cdot k$

**normalization**:

$q = \dfrac{q}{||q||}$

$||q|| = \sqrt{w^2 + x^2 + y^2 + z^2}$

**axis & angle -> quat**

$q = \begin{bmatrix}
\cos(\theta / 2) \\
x \cdot \sin(\theta / 2) \\
y \cdot \sin(\theta / 2) \\
z \cdot \sin(\theta / 2)
\end{bmatrix}$

## Optimization
- don't calculate transformations for points that do not appear on the screen and who have no edge starting or ending with them that do not appear on the screen. If you don't need them for drawing, you don't need to calculate their transformations, and since all different positions of the point are saved together in a struct for each point, I can always check whether a neighbor is visible on the screen.

## Code Structure && Error Handling
- one cleanup function that frees allocated memory tracked in the state struct.
- functions mostly don't return anything, but modify the tracked variables in the state struct, which is passed by reference almost everywhere (especially where a failure can happen that I do not control, ex: system calls, libft stuff, like `get_next_line()` or `ft_split()`)

## MLX
- is a wrapper for the X11 and Xext API

### Behaviour
- the `mlx_ptr` needs to be freed, the `mlx_destroy_display(mlx_ptr)` needs to be called - not documented properly in the man pages.
- the hook needed for closing the display by clicking on the x is not documented in the man page. `mlx_hook` exists as a generic hook, which takes X11 Event(Type)s and Masks.

### X11 Events
The common Types are bold and have the corresponding code in brackets:

| Event Category					| Event Type (Codes) |
| :--								| :-- |
| Keyboard Events					| **KeyPress (2)**, **KeyRelease (3)** |
| Pointer events					| **ButtonPress (4)**, **ButtonRelease (5)**, **MotionNotify (6)** |
| Window crossing events			| EnterNotify, LeaveNotify |
| Input focus events				| FocusIn, FocusOut |
| Keymap state notification event	| KeymapNotify |
| Exposure events					| **Expose (12)**, GraphicsExpose, NoExpose |
| Structure control events			| CirculateRequest, ConfigureRequest, MapRequest, ResizeRequest |
| Window state notification events	| CirculateNotify, ConfigureNotify, CreateNotify, DestroyNotify, GravityNotify, MapNotify, MappingNotify, ReparentNotify, UnmapNotify, VisibilityNotify |
| Colormap state notification event	| ColormapNotify |
| **Client communication events**	| **ClientMessage (33)**, PropertyNotify, SelectionClear, SelectionNotify, SelectionRequest |

### Full List of Event Type Codes
Taken from `/usr/include/X11/X.h`

```C
/*****************************************************************
 * EVENT DEFINITIONS
 *****************************************************************/

/* Input Event Masks. Used as event-mask window attribute and as arguments
   to Grab requests.  Not to be confused with event names.  */

#define NoEventMask					0L
#define KeyPressMask				(1L<<0)
#define KeyReleaseMask				(1L<<1)
#define ButtonPressMask				(1L<<2)
#define ButtonReleaseMask			(1L<<3)
#define EnterWindowMask				(1L<<4)
#define LeaveWindowMask				(1L<<5)
#define PointerMotionMask			(1L<<6)
#define PointerMotionHintMask		(1L<<7)
#define Button1MotionMask			(1L<<8)
#define Button2MotionMask			(1L<<9)
#define Button3MotionMask			(1L<<10)
#define Button4MotionMask			(1L<<11)
#define Button5MotionMask			(1L<<12)
#define ButtonMotionMask			(1L<<13)
#define KeymapStateMask				(1L<<14)
#define ExposureMask				(1L<<15)
#define VisibilityChangeMask		(1L<<16)
#define StructureNotifyMask			(1L<<17)
#define ResizeRedirectMask			(1L<<18)
#define SubstructureNotifyMask		(1L<<19)
#define SubstructureRedirectMask	(1L<<20)
#define FocusChangeMask				(1L<<21)
#define PropertyChangeMask			(1L<<22)
#define ColormapChangeMask			(1L<<23)
#define OwnerGrabButtonMask			(1L<<24)

/* Event names.  Used in "type" field in XEvent structures.  Not to be
   confused with event masks above.  They start from 2 because 0 and 1
   are reserved in the protocol for errors and replies. */

#define KeyPress			2
#define KeyRelease			3
#define ButtonPress			4
#define ButtonRelease		5
#define MotionNotify		6
#define EnterNotify			7
#define LeaveNotify			8
#define FocusIn				9
#define FocusOut			10
#define KeymapNotify		11
#define Expose				12
#define GraphicsExpose		13
#define NoExpose			14
#define VisibilityNotify	15
#define CreateNotify		16
#define DestroyNotify		17
#define UnmapNotify			18
#define MapNotify			19
#define MapRequest			20
#define ReparentNotify		21
#define ConfigureNotify		22
#define ConfigureRequest	23
#define GravityNotify		24
#define ResizeRequest		25
#define CirculateNotify		26
#define CirculateRequest	27
#define PropertyNotify		28
#define SelectionClear		29
#define SelectionRequest	30
#define SelectionNotify		31
#define ColormapNotify		32
#define ClientMessage		33
#define MappingNotify		34
#define GenericEvent		35
#define LASTEvent			36	/* must be bigger than any event # */
```

### Mappings of Keyboard and Mouse Events
full list in `/usr/include/X11/keysymdef.h`

**common keys:**

```C
#define XK_BackSpace	0xff08  /* Back space, back char */
#define XK_Tab			0xff09
#define XK_Return		0xff0d  /* Return, enter */
#define XK_Pause		0xff13  /* Pause, hold */
#define XK_Escape		0xff1b
#define XK_Delete		0xffff  /* Delete, rubout */

#define XK_Home			0xff50
#define XK_Left			0xff51  /* Move left, left arrow */
#define XK_Up			0xff52  /* Move up, up arrow */
#define XK_Right		0xff53  /* Move right, right arrow */
#define XK_Down			0xff54  /* Move down, down arrow */

#define XK_Page_Up		0xff55
#define XK_Page_Down	0xff56
#define XK_End			0xff57  /* EOL */
#define XK_Begin		0xff58  /* BOL */

#define XK_Shift_L		0xffe1  /* Left shift */
#define XK_Shift_R		0xffe2  /* Right shift */
#define XK_Control_L	0xffe3  /* Left control */
#define XK_Control_R	0xffe4  /* Right control */
#define XK_Caps_Lock	0xffe5  /* Caps lock */

#define XK_Meta_L		0xffe7  /* Left meta */
#define XK_Meta_R		0xffe8  /* Right meta */
#define XK_Alt_L		0xffe9  /* Left alt */
#define XK_Alt_R		0xffea  /* Right alt */

#define XK_space		0x0020  /* U+0020 SPACE */
#define XK_exclam		0x0021  /* U+0021 EXCLAMATION MARK */
#define XK_quotedbl		0x0022  /* U+0022 QUOTATION MARK */
#define XK_numbersign	0x0023  /* U+0023 NUMBER SIGN */
#define XK_dollar		0x0024  /* U+0024 DOLLAR SIGN */
#define XK_percent		0x0025  /* U+0025 PERCENT SIGN */
#define XK_ampersand	0x0026  /* U+0026 AMPERSAND */
#define XK_apostrophe	0x0027  /* U+0027 APOSTROPHE */
#define XK_quoteright	0x0027  /* deprecated */
#define XK_parenleft	0x0028  /* U+0028 LEFT PARENTHESIS */
#define XK_parenright	0x0029  /* U+0029 RIGHT PARENTHESIS */
#define XK_asterisk		0x002a  /* U+002A ASTERISK */
#define XK_plus			0x002b  /* U+002B PLUS SIGN */
#define XK_comma		0x002c  /* U+002C COMMA */
#define XK_minus		0x002d  /* U+002D HYPHEN-MINUS */
#define XK_period		0x002e  /* U+002E FULL STOP */
#define XK_slash		0x002f  /* U+002F SOLIDUS */
#define XK_0			0x0030  /* U+0030 DIGIT ZERO */
#define XK_1			0x0031  /* U+0031 DIGIT ONE */
#define XK_2			0x0032  /* U+0032 DIGIT TWO */
#define XK_3			0x0033  /* U+0033 DIGIT THREE */
#define XK_4			0x0034  /* U+0034 DIGIT FOUR */
#define XK_5			0x0035  /* U+0035 DIGIT FIVE */
#define XK_6			0x0036  /* U+0036 DIGIT SIX */
#define XK_7			0x0037  /* U+0037 DIGIT SEVEN */
#define XK_8			0x0038  /* U+0038 DIGIT EIGHT */
#define XK_9			0x0039  /* U+0039 DIGIT NINE */
#define XK_colon		0x003a  /* U+003A COLON */
#define XK_semicolon	0x003b  /* U+003B SEMICOLON */
#define XK_less			0x003c  /* U+003C LESS-THAN SIGN */
#define XK_equal		0x003d  /* U+003D EQUALS SIGN */
#define XK_greater		0x003e  /* U+003E GREATER-THAN SIGN */
#define XK_question		0x003f  /* U+003F QUESTION MARK */
#define XK_at			0x0040  /* U+0040 COMMERCIAL AT */
#define XK_A			0x0041  /* U+0041 LATIN CAPITAL LETTER A */
#define XK_B			0x0042  /* U+0042 LATIN CAPITAL LETTER B */
#define XK_C			0x0043  /* U+0043 LATIN CAPITAL LETTER C */
#define XK_D			0x0044  /* U+0044 LATIN CAPITAL LETTER D */
#define XK_E			0x0045  /* U+0045 LATIN CAPITAL LETTER E */
#define XK_F			0x0046  /* U+0046 LATIN CAPITAL LETTER F */
#define XK_G			0x0047  /* U+0047 LATIN CAPITAL LETTER G */
#define XK_H			0x0048  /* U+0048 LATIN CAPITAL LETTER H */
#define XK_I			0x0049  /* U+0049 LATIN CAPITAL LETTER I */
#define XK_J			0x004a  /* U+004A LATIN CAPITAL LETTER J */
#define XK_K			0x004b  /* U+004B LATIN CAPITAL LETTER K */
#define XK_L			0x004c  /* U+004C LATIN CAPITAL LETTER L */
#define XK_M			0x004d  /* U+004D LATIN CAPITAL LETTER M */
#define XK_N			0x004e  /* U+004E LATIN CAPITAL LETTER N */
#define XK_O			0x004f  /* U+004F LATIN CAPITAL LETTER O */
#define XK_P			0x0050  /* U+0050 LATIN CAPITAL LETTER P */
#define XK_Q			0x0051  /* U+0051 LATIN CAPITAL LETTER Q */
#define XK_R			0x0052  /* U+0052 LATIN CAPITAL LETTER R */
#define XK_S			0x0053  /* U+0053 LATIN CAPITAL LETTER S */
#define XK_T			0x0054  /* U+0054 LATIN CAPITAL LETTER T */
#define XK_U			0x0055  /* U+0055 LATIN CAPITAL LETTER U */
#define XK_V			0x0056  /* U+0056 LATIN CAPITAL LETTER V */
#define XK_W			0x0057  /* U+0057 LATIN CAPITAL LETTER W */
#define XK_X			0x0058  /* U+0058 LATIN CAPITAL LETTER X */
#define XK_Y			0x0059  /* U+0059 LATIN CAPITAL LETTER Y */
#define XK_Z			0x005a  /* U+005A LATIN CAPITAL LETTER Z */
#define XK_bracketleft	0x005b  /* U+005B LEFT SQUARE BRACKET */
#define XK_backslash	0x005c  /* U+005C REVERSE SOLIDUS */
#define XK_bracketright	0x005d  /* U+005D RIGHT SQUARE BRACKET */
#define XK_asciicircum	0x005e  /* U+005E CIRCUMFLEX ACCENT */
#define XK_underscore	0x005f  /* U+005F LOW LINE */
#define XK_grave		0x0060  /* U+0060 GRAVE ACCENT */
#define XK_quoteleft	0x0060  /* deprecated */
#define XK_a			0x0061  /* U+0061 LATIN SMALL LETTER A */
#define XK_b			0x0062  /* U+0062 LATIN SMALL LETTER B */
#define XK_c			0x0063  /* U+0063 LATIN SMALL LETTER C */
#define XK_d			0x0064  /* U+0064 LATIN SMALL LETTER D */
#define XK_e			0x0065  /* U+0065 LATIN SMALL LETTER E */
#define XK_f			0x0066  /* U+0066 LATIN SMALL LETTER F */
#define XK_g			0x0067  /* U+0067 LATIN SMALL LETTER G */
#define XK_h			0x0068  /* U+0068 LATIN SMALL LETTER H */
#define XK_i			0x0069  /* U+0069 LATIN SMALL LETTER I */
#define XK_j			0x006a  /* U+006A LATIN SMALL LETTER J */
#define XK_k			0x006b  /* U+006B LATIN SMALL LETTER K */
#define XK_l			0x006c  /* U+006C LATIN SMALL LETTER L */
#define XK_m			0x006d  /* U+006D LATIN SMALL LETTER M */
#define XK_n			0x006e  /* U+006E LATIN SMALL LETTER N */
#define XK_o			0x006f  /* U+006F LATIN SMALL LETTER O */
#define XK_p			0x0070  /* U+0070 LATIN SMALL LETTER P */
#define XK_q			0x0071  /* U+0071 LATIN SMALL LETTER Q */
#define XK_r			0x0072  /* U+0072 LATIN SMALL LETTER R */
#define XK_s			0x0073  /* U+0073 LATIN SMALL LETTER S */
#define XK_t			0x0074  /* U+0074 LATIN SMALL LETTER T */
#define XK_u			0x0075  /* U+0075 LATIN SMALL LETTER U */
#define XK_v			0x0076  /* U+0076 LATIN SMALL LETTER V */
#define XK_w			0x0077  /* U+0077 LATIN SMALL LETTER W */
#define XK_x			0x0078  /* U+0078 LATIN SMALL LETTER X */
#define XK_y			0x0079  /* U+0079 LATIN SMALL LETTER Y */
#define XK_z			0x007a  /* U+007A LATIN SMALL LETTER Z */
#define XK_braceleft	0x007b  /* U+007B LEFT CURLY BRACKET */
#define XK_bar			0x007c  /* U+007C VERTICAL LINE */
#define XK_braceright	0x007d  /* U+007D RIGHT CURLY BRACKET */
#define XK_asciitilde	0x007e  /* U+007E TILDE */
```

# tmux
## Options
This is how to find out what options are currently set, by default and by the currently active config file:

```
tmux show -g
tmux show -gw    # window options
tmux show -gp    # pane options
```
# vim
## Notation
`n_`, `i_` `v_` for the corresponding mode

## Commands
`n_gt`: go to next tab
`n_gT`: go to previous tab

# scan-build
check it for better compiler flags and checks.

# grep
## flags
`-E` - extended REGEX?

`-n` - line number
`-r` - recursive
`-v` - reverse match
`-w` - word match

# shell hooks

```zsh
preexec() {
  local display_cmd="${(j. .)${${(z)1}:t}}"
  printf '\033]2;%s\033\\' "${display_cmd}"
}

precmd() {
  printf '\033]2;%s\033\\' "${PWD/#$HOME/~}"
}
```
