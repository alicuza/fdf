/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/09 20:37:29 by sancuta          ###   ########.fr       */
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
	t_point		*p;
	void		*mlx_ptr;
	char		*path;
	int			fd;
}	t_state_data;
#endif
