/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:16:52 by sancuta           #+#    #+#             */
/*   Updated: 2026/01/25 21:00:40 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	main(int argc, char **argv)
{
	t_mlx_data	mlx_data;
	int			i;
	int			pixels;
	t_point		**p = NULL;
	t_map		map;

	if (argc != 2)
		return (-1);

	mlx_data.mlx_ptr = mlx_init();
	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, WIN_SIZE_X,
			WIN_SIZE_Y, TITLE);
	mlx_data.img_ptr = mlx_new_image(mlx_data.mlx_ptr, IMG_SIZE_X,
			IMG_SIZE_Y);
	mlx_data.img_buffer = mlx_get_data_addr(mlx_data.img_ptr,
			&mlx_data.bits_per_pixel, &mlx_data.size_line, &mlx_data.endian);
	i = 0;
	pixels = IMG_SIZE_X * IMG_SIZE_Y;
	while (i < pixels)
	{
		*((int *)mlx_data.img_buffer + i) = 0xFFFFFF;
		i++;
	}
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr,
		mlx_data.img_ptr, (WIN_SIZE_X - IMG_SIZE_X) / 2,
		(WIN_SIZE_Y - IMG_SIZE_Y) / 2);
	map = parse(argv[1], &p);
	i = 0;
	while (i < map.width * map.height)
	{
		ft_printf("P[%d] = (%d, %d, %d)\n", i, p[i / map.width][i % map.width].x, p[i / map.width][i % map.width].y, p[i / map.width][i % map.width].z);
		i++;
	}
//	free_points(&p, map);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}
/*
void free_points(t_point ***p, t_map map)
{
	
}
*/
