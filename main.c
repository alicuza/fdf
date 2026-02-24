/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:52:21 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/24 20:14:43 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	for initialization I could use ft_memset(state, 0, sizeof(t_state_data));
	fd = -1, to be able to check if fd is open when doing cleanup.
*/

void	init_trans(t_state_data *state)
{
	state->trans.rot = quat_id();
	state->trans.autorot = 0;
	state->trans.delta_angle = ROT_SPEED;
	state->trans.offset = (t_vec3d){0, 0, 0};
	state->trans.axis = (t_fvec3d){0, 0, 1};
	state->trans.scale = (double)min(IMG_SIZE_X, IMG_SIZE_Y) * 0.50;
}

static void	init_dim(t_state_data *state)
{
	state->win.dim = (t_dim2d){WIN_SIZE_X, WIN_SIZE_Y};
	state->img.dim = (t_dim2d){IMG_SIZE_X, IMG_SIZE_Y};
	state->img.offset_to_win.x = (WIN_SIZE_X - IMG_SIZE_X) * 0.5;
	state->img.offset_to_win.y = (WIN_SIZE_Y - IMG_SIZE_Y) * 0.5;
}

static void	init_state(t_state_data *state, char *path)
{
	*state = (t_state_data){0};
	state->fd = -1;
	init_dim(state);
	if (!path)
		handle_exit(state, EXIT_FAILURE, "prep_drawing");
	state->path = path;
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
	state->img.size = state->img.dim.height * state->img.size_line;
	init_trans(state);
}

int	main(int argc, char **argv)
{
	t_state_data	state;

	if (argc != 2)
		return (ft_printf("error: no map passed\nuse: ./fdf path/to/map\n"), 1);
	init_state(&state, argv[1]);
	get_map_dim(&state);
	init_model(&state);
	mlx_hook(state.win.ptr, KeyPress, KeyPressMask, handle_key_press, &state);
	mlx_hook(state.win.ptr, KeyRelease, KeyReleaseMask,
		handle_key_release, &state);
	mlx_loop_hook(state.mlx_ptr, render, &state);
	mlx_hook(state.win.ptr, ClientMessage, StructureNotifyMask,
		call_exit, &state);
	mlx_loop(state.mlx_ptr);
	return (handle_exit(&state, EXIT_SUCCESS, "main"), 0);
}
