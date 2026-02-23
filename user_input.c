/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:50:01 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/23 22:27:57 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	keycode_to_move(int keycode)
{
	if (keycode == XK_w)
		return (MOVE_XP);
	if (keycode == XK_s)
		return (MOVE_XN);
	if (keycode == XK_a)
		return (MOVE_YP);
	if (keycode == XK_d)
		return (MOVE_YN);
	if (keycode == XK_q)
		return (MOVE_ZP);
	if (keycode == XK_e)
		return (MOVE_ZN);
	return (-1);
}

static int	keycode_to_rot(int keycode)
{
	if (keycode == XK_i)
		return (ROT_YP);
	if (keycode == XK_k)
		return (ROT_YN);
	if (keycode == XK_u)
		return (ROT_XP);
	if (keycode == XK_o)
		return (ROT_XN);
	if (keycode == XK_j)
		return (ROT_ZP);
	if (keycode == XK_l)
		return (ROT_ZN);
	return (-1);
}

static int	keycode_to_zoom(int keycode)
{
	if (keycode == XK_equal)
		return (ZOOM_IN);
	if (keycode == XK_minus)
		return (ZOOM_OUT);
	return (-1);
}

static int	keycode_to_command(int keycode)
{
	int	cmd;

	cmd = keycode_to_move(keycode);
	if (cmd != -1)
		return (cmd);
	cmd = keycode_to_rot(keycode);
	if (cmd != -1)
		return (cmd);
	return (keycode_to_zoom(keycode));
}

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

void	apply_zoom(t_state_data *state)
{
	if (state->key[ZOOM_IN])
		state->trans.scale *= ZOOM_SPEED;
	if (state->key[ZOOM_OUT])
		state->trans.scale /= ZOOM_SPEED;
}

inline static void	get_rotation(t_state_data *state, t_fvec3d axis)
{
	state->trans.rot =
		quat_norm(quat_mult(quat_from_aa(ROT_SPEED, axis), state->trans.rot));
}

void	apply_rotation(t_state_data *state)
{
	if (state->trans.autorot)
		get_rotation(state, AXIS_ZP);
	if (state->key[ROT_XP])
		get_rotation(state, AXIS_XP);
	if (state->key[ROT_XN])
		get_rotation(state, AXIS_XN);
	if (state->key[ROT_YP])
		get_rotation(state, AXIS_YP);
	if (state->key[ROT_YN])
		get_rotation(state, AXIS_YN);
	if (state->key[ROT_ZP])
		get_rotation(state, AXIS_ZP);
	if (state->key[ROT_ZN])
		get_rotation(state, AXIS_ZN);
}

void	apply_translation(t_state_data *state)
{
	if (state->key[MOVE_XP])
		state->trans.offset.x += MOVE_SPEED;
	if (state->key[MOVE_XN])
		state->trans.offset.x -= MOVE_SPEED;
	if (state->key[MOVE_YP])
		state->trans.offset.y += MOVE_SPEED;
	if (state->key[MOVE_YN])
		state->trans.offset.y -= MOVE_SPEED;
	if (state->key[MOVE_ZP])
		state->trans.offset.z += MOVE_SPEED;
	if (state->key[MOVE_ZN])
		state->trans.offset.z -= MOVE_SPEED;
}
