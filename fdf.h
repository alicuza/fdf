/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/04 20:26:42 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_SIZE_X	720
# define WIN_SIZE_Y	480
# define IMG_SIZE_X	480
# define IMG_SIZE_Y	360
# define TITLE		"EAT MY SHORTS"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>

typedef struct s_img_data
{
	void	*bg_ptr;
	void	*fg_ptr;
	char	*bg_buf;
	char	*fg_buf;
}	t_img_data;

typedef struct s_mlx_data
{
	t_img_data	images;
	void		*mlx_ptr;
	void		*win_ptr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}	t_mlx_data;

typedef struct s_dim2
{
	int	height;
	int	width;
}	t_dim2;

typedef struct s_dim3
{
	int	height;
	int	width;
	int	depth;
}	t_dim3;

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_vector3
{
	int	x;
	int	y;
	int	z;
}	t_vector3;

typedef struct s_point
{
	t_vector3	map;
	t_vector2	pix;
}	t_point;

typedef struct s_map
{
	t_dim2		dimension;
	t_vector2	scalar;
}	t_map;

t_map parse(const char *path, t_point ***point);
int	draw_lines_from_point(t_mlx_data *data, t_point **p, t_map map);
#endif
