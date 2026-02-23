/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/23 08:23:37 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_SIZE_X 720
# define WIN_SIZE_Y 480
# define IMG_SIZE_X 480
# define IMG_SIZE_Y 360
# define TITLE "sancuta's magical fildefer"
# define M_SQRT1_3 0.57735026918962576451
# define M_SQRT1_6 0.40824829046386301636
# define M_SQRT2_3 0.81649658092772603273
# define M_SQRT3_HALF 0.86602540378443864676
# define EPSILON 1e-9
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>

typedef enum e_proj
{
	ISO,
	DIM,
}	t_proj;

typedef struct s_dim2d
{
	int	width;
	int	height;
}	t_dim2d;

typedef struct s_vec2d
{
	int	x;
	int	y;
}	t_vec2d;

typedef struct s_fvec2d
{
	double	x;
	double	y;
}	t_fvec2d;

typedef struct s_vec2d_arr
{
	int	*x;
	int	*y;
}	t_vec2d_arr;

typedef struct s_fvec2d_arr
{
	double	*x;
	double	*y;
}	t_fvec2d_arr;

typedef struct s_fvec3d_arr
{
	double	*x;
	double	*y;
	double	*z;
}	t_fvec3d_arr;

typedef struct s_fvec3d
{
	double	x;
	double	y;
	double	z;
}	t_fvec3d;

typedef struct s_quat
{
	double	w;
	double	x;
	double	y;
	double	z;
}	t_quat;

typedef struct s_mat4
{
	double	pos[16];
}	t_mat4;

typedef struct s_pnt_data
{
	t_fvec3d_arr	model;
	t_fvec3d_arr	world;
	t_vec2d_arr		screen;
}	t_pnt_data;

typedef struct s_img_data
{
	t_vec2d	offset_to_win;
	t_dim2d	dim;
	void	*ptr;
	char	*buf;
	size_t	size;
	int		bits_ppix;
	int		size_line;
	int		endian;
}	t_img_data;

typedef struct s_win_data
{
	t_dim2d	dim;
	void	*ptr;
}	t_win_data;

typedef struct s_map_data
{
	t_dim2d	dim;
	size_t	size;
}	t_map_data;

// delta_angle is in radians;

typedef struct s_trans_data
{
	t_quat		rot;
	t_fvec3d	axis;
	t_fvec3d	offset;
	double		delta_angle;
	double		scale;
}	t_trans_data;

typedef struct s_state_data
{
	t_img_data		img;
	t_win_data		win;
	t_map_data		map;
	t_pnt_data		p;
	t_trans_data	trans;
	t_proj			proj;
	void			*mlx_ptr;
	char			*path;
	char			*gnl_line;
	int				fd;
}	t_state_data;

// init
void			init_model(t_state_data *state);
void			center_norm_model(t_state_data *state);
void			get_map_dim(t_state_data *state);

//math
t_mat4			mat4_id(void);
t_mat4			mat_iso(void);
t_mat4			mat_21(void);
t_mat4			mat4_mult(t_mat4 m1, t_mat4 m2);
t_mat4			generate_trs_mat(t_fvec3d transform, t_quat q, double scale);
t_quat			quat_id(void);
t_quat			quat_from_aa(double rad, t_fvec3d axis);
t_quat			quat_mult(t_quat q1, t_quat q2);
t_quat			quat_norm(t_quat q);
void			p_soa_trs_mult_3d(t_fvec3d_arr *p0, t_fvec3d_arr *p1,
					size_t size, t_mat4 m);
void			p_soa_trs_mult_2d(t_fvec3d_arr *p0, t_vec2d_arr *p1,
					size_t size, t_mat4 m);
t_fvec3d		vec_norm(t_fvec3d v);
t_fvec3d_arr	vec_soa_norm(t_fvec3d_arr v, size_t len);
int				min(int n1, int n2);

//unused
int				max(int n1, int n2);
double			deg_to_rad(double deg);
double			rad_to_deg(double rad);

// loop
void			draw(t_state_data *state);
int				handle_key_press(int keycode, void *param);
int				render(void *data);
int				call_exit(void *param);

// exiting
void			handle_exit(t_state_data *state, int exit_status,
					const char *caller);
void			free_str(char **str);
void			free_str_arr(char ***str_arr);
#endif
