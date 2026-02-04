/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:00:51 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/04 20:31:14 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw_line(t_mlx_data *data, int x1, int y1, int x2, int y2);

int	draw_lines_from_point(t_mlx_data *data, t_point **p, t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.dimension.height)
	{
		j = 0;
		while (j < map.dimension.width)
		{
			if (i < map.dimension.height - 1)
				draw_line(data, p[i][j].pix.x, p[i][j].pix.y, p[i + 1][j].pix.x, p[i + 1][j].pix.y);
			if (i < map.dimension.width - 1)
				draw_line(data, p[i][j].pix.x, p[i][j].pix.y, p[i][j + 1].pix.x, p[i][j + 1].pix.y);
			j++;
		}
		i++;
	}
}

// do i need to find out the orientation of the line necessarily?

int	draw_line(t_mlx_data *data, int x1, int y1, int x2, int y2)
{
	int		i;
	int		j;
	int		delta_x;
	int		delta_y;
	int		sign_x;
	int		sign_y;
	int		pix_index;
	double	slope;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	if (delta_x < 0)
		sign_x = -1;
	if (delta_y < 0)
		sign_y = -1;
	if (delta_y == 0)
		slope = // considering it TODO
	else
		slope = delta_x / delta_y;
	i = 0
	while (i < delta_y * sign_y)
	{
		j = 0;
		while (j < delta_x * sign_x)
		{
			pix_index = (y1 + i * sign_y) * map.dimension.width + x1 + j * sign_x;
			*((int *)data->images.fg_buf + pix_index = 0x0f0f0f;
		}
		i++;
	}
}
