/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/16 13:38:31 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_SIZE_X 720
# define WIN_SIZE_Y 480
# define IMG_SIZE_X 480
# define IMG_SIZE_Y 360
# define TITLE "sancuta's magical fildefer"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_dim2d
{
	int	height;
	int	width;
}	t_dim2d;

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
	t_fvec2d_arr	screen;
}	t_pnt_data;

typedef struct s_img_data
{
	t_dim2d	dim;
	void	*ptr;
	char	*buf;
	int		bits_ppix;
	int		size_line;
	int		endian;
	int		offset_from_win;
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

typedef struct s_state_data
{
	t_img_data	img;
	t_win_data	win;
	t_map_data	map;
	t_pnt_data	p;
	void		*mlx_ptr;
	char		*path;
	char		*gnl_line;
	int			fd;
}	t_state_data;
#endif
