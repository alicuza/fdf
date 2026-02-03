/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/03 13:11:47 by sancuta          ###   ########.fr       */
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

typedef struct s_img_data
{
	void	*bg_ptr;
	void	*fg_ptr;
	char	*bg_buf;
	char	*fg_buf;
}			t_img_data;

typedef struct s_mlx_data
{
	t_img_data	images;
	void		*mlx_ptr;
	void		*win_ptr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_mlx_data;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}		t_point;

typedef struct s_map
{
	int	height;
	int	width;
}		t_map;

t_map parse(const char *path, t_point ***point);

#endif
