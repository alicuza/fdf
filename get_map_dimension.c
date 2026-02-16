/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_dimension.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:06:09 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/17 00:04:57 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	arr_len(char **str_arr)
{
	int i;

	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}

static void	arr_dim(t_state_data *state, char *line)
{
	char	**split_line;
	int		line_len;

	split_line = ft_split(line, ' ');
	if (!split_line)
		handle_exit(state, EXIT_FAILURE, "arr_dim");
	line_len = arr_len(split_line);
	if (!state->map.dim.width)
		state->map.dim.width = line_len;
	if (!state->map.dim.width)
		handle_exit(state, EXIT_FAILURE, "arr_dim");
	state->map.dim.height++;
	if (state->map.dim.width != line_len)
		handle_exit(state, EXIT_FAILURE, "arr_dim");
	free_str_arr(&split_line);
}

void	get_map_dim(t_state_data *state)
{
	char	*cur_line;

	state->fd = open(state->path, O_RDONLY);
	if (state->fd == -1)
		handle_exit(state, EXIT_FAILURE, "get_map_dim");
	while (1)
	{
		errno = 0;
		cur_line = get_next_line(state->fd);
		if (!cur_line)
		{
			if (errno)
				handle_exit(state, EXIT_FAILURE, "get_map_dim");
			break;
		}
		arr_dim(state, cur_line);
		free_str(&cur_line);
	}
	close(state->fd);
	state->fd = -1;
	if (state->map.dim.height == 0)
		handle_exit(state, EXIT_FAILURE, "get_map_dim");
	state->map.size = state->map.dim.width * state->map.dim.height;
}
