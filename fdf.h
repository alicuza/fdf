/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/01/22 18:04:38 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_SIZE_X	720
# define WIN_SIZE_Y	480
# define IMG_SIZE_X	480
# define IMG_SIZE_Y	360
# define TITLE		"EAT MY SHORTS"

typedef struct	s_mlx_data
{
	void		*mlx_ptr;
	void		*img_ptr;
	void		*win_ptr;
	char		*img_buffer;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_mlx_data;

#endif
