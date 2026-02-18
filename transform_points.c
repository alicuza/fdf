/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_points.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:58:49 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/18 12:53:02 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	model_to_world(t_state_data *state)
{
	t_quat		delta_q;
	t_mat4		trs_mat;

	state->trans.delta_angle = 0.0005;
	state->trans.axis = (t_fvec3d){0, 0, 1};

	if (fabs(state->trans.delta_angle) >= FLT_EPSILON)
	{
		delta_q = quat_from_aa(state->trans.delta_angle, state->trans.axis);
		state->trans.rot = quat_norm(quat_mult(delta_q, state->trans.rot));
		state->trans.delta_angle = 0.0;
	}
	trs_mat = generate_trs_mat(state->trans.offset, state->trans.rot,
			state->trans.scale);
	p_soa_trs_mult_3d(&state->p.model, &state->p.world, state->map.size,
					trs_mat);
}

//TODO change trs_mat and proj_mat to mat_trs and mat_proj

void	world_to_screen(t_state_data *state)
{
	t_mat4		proj_mat;

	proj_mat = new_mat_iso();
/*	if (state->proj == DIM)
		proj_mat = new_mat_21();
	else
		proj_mat = new_mat_iso();
*/	p_soa_trs_mult_2d(&state->p.world, &state->p.screen,
					state->map.size, proj_mat);
}

int	render(void *data)
{
	t_state_data	*state;

	state = (t_state_data *)data;
	model_to_world(state);
	world_to_screen(state);
	draw(state);
	return (1);
}
