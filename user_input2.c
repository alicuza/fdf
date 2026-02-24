/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:57:35 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/24 20:13:30 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_zoom(t_state_data *state)
{
	if (state->key[ZOOM_IN])
		state->trans.scale = fmin(state->trans.scale * ZOOM_SPEED, 10000);
	if (state->key[ZOOM_OUT])
		state->trans.scale = fmax(state->trans.scale / ZOOM_SPEED, 1);
}

inline static void	get_rotation(t_state_data *state, t_fvec3d axis)
{
	state->trans.rot = quat_norm(quat_mult(quat_from_aa(ROT_SPEED, axis),
				state->trans.rot));
}

void	apply_rotation(t_state_data *state)
{
	if (state->trans.autorot)
		get_rotation(state, (t_fvec3d){0, 0, 1});
	if (state->key[ROT_XP])
		get_rotation(state, (t_fvec3d){1, 0, 0});
	if (state->key[ROT_XN])
		get_rotation(state, (t_fvec3d){-1, 0, 0});
	if (state->key[ROT_YP])
		get_rotation(state, (t_fvec3d){0, 1, 0});
	if (state->key[ROT_YN])
		get_rotation(state, (t_fvec3d){0, -1, 0});
	if (state->key[ROT_ZP])
		get_rotation(state, (t_fvec3d){0, 0, 1});
	if (state->key[ROT_ZN])
		get_rotation(state, (t_fvec3d){0, 0, -1});
}

void	apply_translation(t_state_data *state)
{
	if (state->key[MOVE_XP])
		state->trans.offset.x = min(state->trans.offset.x + MOVE_SPEED, 2000);
	if (state->key[MOVE_XN])
		state->trans.offset.x = max(state->trans.offset.x - MOVE_SPEED, -2000);
	if (state->key[MOVE_YP])
		state->trans.offset.y = min(state->trans.offset.y + MOVE_SPEED, 2000);
	if (state->key[MOVE_YN])
		state->trans.offset.y = max(state->trans.offset.y - MOVE_SPEED, -2000);
	if (state->key[MOVE_ZP])
		state->trans.offset.z = min(state->trans.offset.z + MOVE_SPEED, 2000);
	if (state->key[MOVE_ZN])
		state->trans.offset.z = max(state->trans.offset.z - MOVE_SPEED, -2000);
}
