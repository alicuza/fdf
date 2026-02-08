/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/08 22:56:25 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_SIZE_X 720
# define WIN_SIZE_Y 480
# define IMG_SIZE_X 480
# define IMG_SIZE_Y 360
# define TITLE "EAT MY SHORTS"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>

typedef struct s_dim2d
{
	int	height;
	int	width;
}	t_dim2d;

typedef struct s_dim3d
{
	int	height;
	int	width;
	int	depth;
}	t_dim3d;

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

typedef struct s_vec3d
{
	int	x;
	int	y;
	int	z;
}	t_vec3d;

typedef struct s_fvec3d
{
	double	x;
	double	y;
	double	z;
}	t_fvec3d;

typedef struct s_point
{
	t_fvec3d	world;
	t_fvec2d	screen;
	t_vec3d		map;
}	t_point;

typedef struct s_img_data
{
	t_dim2d	dim;
	void	*ptr;
	char	*buf;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		offset_from_win;
}	t_img_data;

typedef struct s_win_data
{
	t_dim2d	dim;
	void	*ptr;
}	t_win_data;

typedef struct s_mlx_data
{
	t_img_data	img;
	t_win_data	win;
	void		*ptr;
}	t_mlx_data;

typedef struct s_map
{
	t_dim2d	dimension;
}	t_map;

void prep_drawing(t_mlx_data *data);
#endif
