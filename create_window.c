/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:16:52 by sancuta           #+#    #+#             */
/*   Updated: 2026/01/22 19:24:55 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_mlx_data	mlx_data;
	int			i;
	int			pixels;
	t_point		*p;

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
	mlx_loop(mlx_data.mlx_ptr);
	*p = parse(argv[1]);
	ft_printf("P = (%d, %d, %d)", p->x, p->y, p->z);
	return (0);
}
