/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:16:52 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/03 13:43:56 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	main(int argc, char **argv)
{
	t_mlx_data	mlx_data;
	int			i;
	int			j;
	int			pixels;
	t_point		**p;
	t_map		map;
	double		wtoi_x;
	double		wtoi_y;

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
		*((int *)mlx_data.images.bg_buf + i) = 0x616569;
		i++;
	}
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr,
		mlx_data.images.bg_ptr, (WIN_SIZE_X - IMG_SIZE_X) / 2,
		(WIN_SIZE_Y - IMG_SIZE_Y) / 2);
	map = parse(argv[1], &p);
	wtoi_x = (double)IMG_SIZE_X / (map.width - 1.0);
	wtoi_y = (double)IMG_SIZE_Y / (map.height - 1.0);
	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr,
					(WIN_SIZE_X - IMG_SIZE_X) / 2 + j * wtoi_x,
					(WIN_SIZE_Y - IMG_SIZE_Y) / 2 + i * wtoi_y, 0xFFFFFF);
			ft_printf("P[%d] = (%d, %d, %d)\n", i * map.width + j, p[i][j].x,
					p[i][j].y, p[i][j].z);
			j++;
		}
		i++;
	}
//	free_points(&p, map);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}

// think about the possibility of any of this failing, how should errors be handled?

//void	set_background

/*
void free_points(t_point ***p, t_map map)
{
	
}
*/
