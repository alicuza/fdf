/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:16:52 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/04 20:30:08 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_press(int key, void *param);
int	clean_exit(t_mlx_data *param);

int	main(int argc, char **argv)
{
	t_mlx_data	mlx_data;
	int			i;
	int			j;
	int			pixels;
	t_point		**p;
	t_map		map;
	int			img_offset_x;
	int			img_offset_y;
	int			pix_index; // for print debugging - can be deleted

	if (argc != 2)
		return (-1);

	p = (t_point **){0};
	map = (t_map){0};
	mlx_data.mlx_ptr = mlx_init();
	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, WIN_SIZE_X,
			WIN_SIZE_Y, TITLE);
	mlx_data.images.bg_ptr = mlx_new_image(mlx_data.mlx_ptr, IMG_SIZE_X,
			IMG_SIZE_Y);
	mlx_data.images.fg_ptr = mlx_new_image(mlx_data.mlx_ptr, IMG_SIZE_X,
			IMG_SIZE_Y);
	mlx_data.images.bg_buf = mlx_get_data_addr(mlx_data.images.bg_ptr,
			&mlx_data.bits_per_pixel, &mlx_data.size_line, &mlx_data.endian);
	mlx_data.images.fg_buf = mlx_get_data_addr(mlx_data.images.fg_ptr,
			&mlx_data.bits_per_pixel, &mlx_data.size_line, &mlx_data.endian);
	i = 0;
	pixels = IMG_SIZE_X * IMG_SIZE_Y;
	while (i < pixels)
	{
		*((int *)mlx_data.images.bg_buf + i) = 0x0f0f0f;
		i++;
	}
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr,
		mlx_data.images.bg_ptr, (WIN_SIZE_X - IMG_SIZE_X) / 2,
		(WIN_SIZE_Y - IMG_SIZE_Y) / 2);
	map = parse(argv[1], &p);
	img_offset_x = (WIN_SIZE_X - IMG_SIZE_X) / 2.0;
	img_offset_y = (WIN_SIZE_Y - IMG_SIZE_Y) / 2.0;
	i = 0;
	while (i < map.dimension.height)
	{
		j = 0;
		while (j < map.dimension.width)
		{
			p[i][j].pix.x = img_offset_x + j * map.scalar.x;
			p[i][j].pix.y = img_offset_y + i * map.scalar.y;
			pix_index = i * map.dimension.width + j;
			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr,
					p[i][j].pix.x, p[i][j].pix.y, 0xFFFFFF);
			ft_printf("P[%03d] = (%2d, %2d, %2d) at position (%3d, %3d)\n",
					pix_index, p[i][j].map.x, p[i][j].map.y, p[i][j].map.z,
					p[i][j].pix.x, p[i][j].pix.y);
			j++;
		}
		i++;
	}
	draw_lines_from_point(&mlx_data, p, map);
//	free_points(&p, map);
	mlx_key_hook(mlx_data.win_ptr, handle_key_press, &mlx_data);
	mlx_hook(mlx_data.win_ptr, 33, 1L<<17, clean_exit, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}

int	handle_key_press(int key, void *param)
{
	if (key == 0xff1b)
	{
		clean_exit((t_mlx_data *)param);
	}
	return (0);
}

// TODO write a proper clean_exit funciton.

int	clean_exit(t_mlx_data *param)
{
	(void)param;
	exit(0);
}

//void	set_background

/*
void free_points(t_point ***p, t_map map)
{
	
}
*/
