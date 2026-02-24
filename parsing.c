/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:11:12 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/24 20:50:54 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	alloc_points(t_state_data *state)
{
	state->p.model.x = ft_calloc(state->map.size, sizeof(double));
	state->p.model.y = ft_calloc(state->map.size, sizeof(double));
	state->p.model.z = ft_calloc(state->map.size, sizeof(double));
	state->p.world.x = ft_calloc(state->map.size, sizeof(double));
	state->p.world.y = ft_calloc(state->map.size, sizeof(double));
	state->p.world.z = ft_calloc(state->map.size, sizeof(double));
	state->p.screen.x = ft_calloc(state->map.size, sizeof(int));
	state->p.screen.y = ft_calloc(state->map.size, sizeof(int));
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

	state->split_line = ft_split(state->gnl_line, ' ');
	if (!state->split_line)
		handle_exit(state, EXIT_FAILURE, "parse_row");
	i = 0;
	while (state->split_line[i])
	{
		ind = i + row * state->map.dim.width;
		state->p.model.x[ind] = (double)i;
		state->p.model.y[ind] = (double)row;
		state->p.model.z[ind] = (double)ft_atoi(state->split_line[i]);
		i++;
	}
	free_str_arr(&(state->split_line));
}

void	init_model(t_state_data *state)
{
	unsigned int	i;

	alloc_points(state);
	state->fd = open(state->path, O_RDONLY);
	if (state->fd == -1)
		handle_exit(state, EXIT_FAILURE, "init_model");
	i = 0;
	while (i < state->map.dim.height)
	{
		state->gnl_line = get_next_line(state->fd);
		if (!state->gnl_line)
			handle_exit(state, EXIT_FAILURE, "init_model");
		parse_row(state, i);
		free_str(&state->gnl_line);
		i++;
	}
	center_norm_model(state);
	close(state->fd);
	state->fd = -1;
}

t_fvec3d	get_center(t_state_data *state)
{
	size_t		i;
	double		z_min;
	double		z_max;
	t_fvec3d	res;

	z_min = state->p.model.z[0];
	z_max = state->p.model.z[0];
	i = 1;
	while (i < state->map.size)
	{
		if (state->p.model.z[i] < z_min)
			z_min = state->p.model.z[i];
		if (state->p.model.z[i] > z_max)
			z_max = state->p.model.z[i];
		i++;
	}
	res.x = (state->map.dim.width - 1.0) / 2.0;
	res.y = (state->map.dim.height - 1.0) / 2.0;
	res.z = (z_max + z_min) / 2.0;
	return (res);
}

void	center_norm_model(t_state_data *state)
{
	size_t		i;
	t_fvec3d	offset;

	offset = get_center(state);
	i = 0;
	while (i < state->map.size)
	{
		state->p.model.x[i] -= offset.x;
		state->p.model.y[i] -= offset.y;
		state->p.model.z[i] -= offset.z;
		i++;
	}
	state->p.model = vec_soa_norm(state->p.model, state->map.size);
}
