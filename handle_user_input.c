/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:59:34 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/24 18:59:57 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_press(int keycode, void *param)
{
	t_state_data	*state;
	int				cmd;

	state = (t_state_data *)param;
	if (keycode == XK_Escape)
		handle_exit(state, EXIT_SUCCESS, "handle_key_press");
	if (keycode == XK_y)
		init_trans(state);
	if (keycode == XK_r)
		state->trans.autorot = !state->trans.autorot;
	if (keycode == XK_c)
		state->proj = (state->proj + 1) % PROJ_CNT;
	cmd = keycode_to_command(keycode);
	if (cmd != -1)
		state->key[cmd] = 1;
	return (0);
}

int	handle_key_release(int keycode, void *param)
{
	t_state_data	*state;
	int				cmd;

	state = (t_state_data *)param;
	cmd = keycode_to_command(keycode);
	if (cmd != -1)
		state->key[cmd] = 0;
	return (0);
}
