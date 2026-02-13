/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:52:21 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/13 15:55:20 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	for initialization I could use ft_memset(state, 0, sizeof(t_state_data));
	fd = -1, to be able to check if fd is open when doing cleanup.
*/

static void	init_state(t_state_data *state, char *path)
{
	*state = (t_state_data){0};
	state->fd = -1;
	state->win.dim = (t_dim2d){WIN_SIZE_X, WIN_SIZE_Y};
	state->img.dim = (t_dim2d){IMG_SIZE_X, IMG_SIZE_Y};
	state->path = path;
	if (!state->path)
		handle_exit(state, EXIT_FAILURE, "prep_drawing");
	state->mlx_ptr = mlx_init();
	if (!state->mlx_ptr)
		handle_exit(state, EXIT_FAILURE, "prep_drawing");
	state->win.ptr = mlx_new_window(state->mlx_ptr,
						state->win.dim.width, state->win.dim.height, "fdf");
	if (!state->win.ptr)
		handle_exit(state, EXIT_FAILURE, "prep_drawing");
	state->img.ptr = mlx_new_image(state->mlx_ptr,
						state->img.dim.width, state->img.dim.height);
	if (!state->img.ptr)
		handle_exit(state, EXIT_FAILURE, "prep_drawing");
	state->img.buf = mlx_get_data_addr(state->img.ptr, &state->img.bits_ppix,
						&state->img.size_line, &state->img.endian);
	if (!state->img.buf)
		handle_exit(state, EXIT_FAILURE, "prep_drawing");
}

int	main(int argc, char **argv)
{
	t_state_data	state;

	if (argc != 2)
		return (ft_printf("error: no map passed\nusage: ./fdf path/to/map"), 1);
	init_state(&state, argv[1]);
	get_map_dim(&state);
	parse_map(&state);
	rotate_points(&state); //TODO
	translate_points(&state); //TODO
	rotate_world(&state); //TODO
	return (handle_exit(&state, EXIT_SUCCESS, "main"), 0);
}
