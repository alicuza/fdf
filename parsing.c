/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:11:12 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/09 21:25:11 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_points(t_state *state)
{
	state->p = malloc(state->map.dim.height * state->map.dim.width * sizeof(t_point));
	if (!state->p)
		handle_exit(state, EXIT_FAILURE, "init_points");
}

/*
	returns the width of the array, validates and assigns each
	member of the p array their correspoinding map coordinates
*/

static void	parse_row(t_state *state, char *line, int row)
{
	int		i;
	int		index;
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line)
		handle_exit(state, EXIT_FAILURE, "parse_map");
	i = 0;
	while (split_line[i])
	{
		index = i + row * state->map.dim.width;
		state->p[index].map.x = i;
		state->p[index].world.x = (double)i;
		state->p[index].map.y = row;
		state->p[index].world.y = (double)row;
		state->p[index].map.z = ft_atoi(split_line[i]);
		state->p[index].world.z = (double)ft_atoi(split_line[i]);
		i++;
	}
	free_str_arr(&split_line);
}

void	parse_map(t_state *state)
{
	int		i;
	char	*cur_line;

	init_points(state);
	state->fd = open(state->path, O_RDONLY);
	if (state->fd == -1)
		handle_exit(state, EXIT_FAILURE, "parse_map");
	errno = 0;
	cur_line = get_next_line(state->fd);
	if (!cur_line && errno != 0)
		handle_exit(state, EXIT_FAILURE, "parse_map");
	i = 0;
	while (i < state->map.dim.height && cur_line)
	{
		parse_row(state, cur_line, i);
		free_str(&cur_line);
		errno = 0;
		cur_line = get_next_line(state->fd);
		if (!cur_line && errno != 0)
			handle_exit(state, EXIT_FAILURE, "parse_map");
		i++;
	}
	if (i < state->map.dim.height)
		handle_exit(state, EXIT_FAILURE, "parse_map");
	close(state->fd);
}
