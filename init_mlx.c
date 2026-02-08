/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:52:21 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/08 20:01:21 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	prep_drawing(t_mlx_data *data)
{
	data->ptr = mlx_init();
	data->win.ptr = mlx_new_window(data->ptr,
						data->win.dim.width, data->win.dim.height, "fdf");
	data->img.ptr = mlx_new_image(data->img.dim.width, data->img.dim.height);
	data->img.buf = mlx_get_data_addr(data->img.ptr, &data->img.bits_per_pixel,
						&data->img.size_line, &data->img.endian);
	return ;
}

t_map	parse_map(const char *path, t_point *p)
{
	char	*cur_line;
	char	**split_line;
	int		fd;
	int		i;
	t_map	map;

	map = (t_map){0};
	map.dim = arr_dim(path);
	fd = open(path, = O_RDONLY);
	cur_line = get_next_line(fd);
}
