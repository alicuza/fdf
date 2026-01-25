/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/01/25 20:33:49 by sancuta          ###   ########.fr       */
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

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*img_ptr;
	void	*win_ptr;
	char	*img_buffer;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}			t_mlx_data;

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
