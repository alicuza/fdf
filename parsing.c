/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:11:12 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/13 15:39:54 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_points(t_state_data *state)
{

	state->p.model.x = ft_calloc(state->map.size * sizeof(double));
	state->p.model.y = ft_calloc(state->map.size * sizeof(double));
	state->p.model.z = ft_calloc(state->map.size * sizeof(double));
	state->p.world.x = ft_calloc(state->map.size * sizeof(double));
	state->p.world.y = ft_calloc(state->map.size * sizeof(double));
	state->p.world.z = ft_calloc(state->map.size * sizeof(double));
	state->p.screen.x = ft_calloc(state->map.size * sizeof(double));
	state->p.screen.y = ft_calloc(state->map.size * sizeof(double));
	if (!state->p.model.x || !state->p.model.y || !state->p.model.z
		|| !state->p.world.x || !state->p.world.y || !state->p.world.z
		|| !state->p.screen.x || !state->p.screen.y)
		handle_exit(state, EXIT_FAILURE, "init_points");
}

/*
	returns the width of the array, validates and assigns each
	member of the p array their correspoinding map coordinates
*/

static void	parse_row(t_state_data *state, int row)
{
	int			i;
	int			ind;
	char		**split_line;
	t_fvec2d	offset;

	split_line = ft_split(state->gnl_line, ' ');
	if (!split_line)
		handle_exit(state, EXIT_FAILURE, "parse_map");
	offset.x = (state->map.dim.width - 1) / 2.0;
	offset.y = (state->map.dim.height - 1) / 2.0;
	i = 0;
	while (split_line[i])
	{
		ind = i + row * state->map.dim.width;
		state->p.model.x[ind] = (double)i - offset.x;
		state->p.model.y[ind] = (double)row - offset.y;
		state->p.model.z[ind] = (double)ft_atoi(split_line[i]);
		state->p.world.x[ind] = state->p.model.x[ind];
		state->p.world.y[ind] = state->p.model.y[ind];
		state->p.world.z[ind] = state->p.model.z[ind];
		i++;
	}
	free_str_arr(&split_line);
}

void	parse_map(t_state_data *state)
{
	int		i;

	init_points(state);
	state->fd = open(state->path, O_RDONLY);
	if (state->fd == -1)
		handle_exit(state, EXIT_FAILURE, "parse_map");
	i = 0;
	while (i < state->map.dim.height)
	{
		state->gnl_line = get_next_line(state->fd);
		if (!state->gnl_line)
			handle_exit(state, EXIT_FAILURE, "parse_map");
		parse_row(state, i);
		free_str(&state->gnl_line);
		i++;
	}
	close(state->fd);
	state->fd = -1;
}
