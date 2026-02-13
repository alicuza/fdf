/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:00:51 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/05 18:00:46 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw_line(t_mlx_data *data, t_point p1, t_point p2);
int	draw_vertical_line(t_mlx_data *data, t_point p1, t_point p2, int sign_y);
int	draw_horizontal_line(t_mlx_data *data, t_point p1, t_point p2, int sign_x);

int	draw_lines(t_mlx_data *data, t_point **p, t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.dimension.height)
	{
		j = 0;
		while (j < map.dimension.width)
		{
			if (i + 1 < map.dimension.height)
				draw_line(data, p[i][j], p[i + 1][j]);
			if (j + 1 < map.dimension.width)
				draw_line(data, p[i][j], p[i][j + 1]);
			j++;
		}
		i++;
	}
	return (1);
}

// do i need to find out the orientation of the line necessarily?

int	draw_line(t_mlx_data *data, t_point p1, t_point p2)
{
	double	i;
	double	j;
	int		delta_x;
	int		delta_y;
	int		sign_x;
	int		sign_y;
	int		pix_index;
	double	slope;
	double	v_intercept;
	double	step_size;
	int		loop_count;

	delta_x = p2.pix.x - p1.pix.x;
	delta_y = p2.pix.y - p1.pix.y;
	step_size = 0;
	sign_x = 1;
	sign_y = 1;
	if (delta_x < 0)
		sign_x = -1;
	if (delta_y < 0)
		sign_y = -1;

	ft_printf("Drawing line from (%d,%d) to (%d,%d), delta_x=%d, delta_y=%d\n",
		p1.pix.x, p1.pix.y, p2.pix.x, p2.pix.y, delta_x, delta_y);

	if (delta_x == 0)
	{
		draw_vertical_line(data, p1, p2, sign_y);
		return (1);
	}
	slope = (double)delta_y / delta_x;
	v_intercept = p1.pix.y - p1.pix.x * slope;
	
	if (delta_y == 0)
	{
		draw_horizontal_line(data, p1, p2, sign_x);
		return (1);
	}
	step_size = (double)delta_x / delta_y * sign_y;

	printf("slope=%.3f, step_size=%.3f\n", slope, step_size);

	i = p1.pix.y;
	j = p1.pix.x;
	loop_count = 0;
	while (j * sign_x <= p2.pix.x * sign_x)
	{
		pix_index = (int)i * data->size_line + (int)j * (data->bits_ppix / 8);
		if (j >= 0 && j < IMG_SIZE_X && i >= 0 && i < IMG_SIZE_Y)
			*(unsigned int *)(data->images.bg_buf + pix_index) = 0x00ffffff;
		j += step_size;
		i = slope * j + v_intercept;
		loop_count++;
	}
	printf("Loop executed %d times\n", loop_count);
	return (1);
}

int	draw_vertical_line(t_mlx_data *data, t_point p1, t_point p2, int sign_y)
{
	double	j;
	int		pix_index;

	j = p1.pix.y;
	while (j * sign_y < p2.pix.y * sign_y)
	{
		pix_index = (int)j * data->size_line + (int)p1.pix.x * (data->bits_ppix / 8);
		if(p1.pix.x >= 0 && p1.pix.x < IMG_SIZE_X && j >= 0 && j < IMG_SIZE_Y)
			*(unsigned int *)(data->images.bg_buf + pix_index) = 0x00ffffff;
		j += sign_y;
	}
	return (1);
}

int	draw_horizontal_line(t_mlx_data *data, t_point p1, t_point p2, int sign_x)
{
	double	i;
	int		pix_index;

	i = p1.pix.x;
	while (i * sign_x < p2.pix.x * sign_x)
	{
		pix_index = (int)p1.pix.y * data->size_line + (int)i * (data->bits_ppix / 8);
		if(i >= 0 && i < IMG_SIZE_X && p1.pix.y >= 0 && p1.pix.y < IMG_SIZE_Y)
			*(unsigned int *)(data->images.bg_buf + pix_index) = 0x00ffffff;
		i += sign_x;
	}
	return (1);
}
