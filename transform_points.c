/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_points.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:58:49 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/16 21:54:08 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void transform_point_arr(t_state_data *state, double angle, double scale, t_fvec3d move)
{
	t_mat4		trs;
	t_quat		rot;
	t_fvec3d	rot_axis;
	size_t		i;

	rot_axis = (t_fvec3d){0, 1, 0};
	rotation = quat_from_aa(deg_to_rad(angle), rot_axis);
	trs = generate_trs_mat(move, rotation, scale);
	i = 0;
	while (i < s->map.size)
	{
		point = (t_fvec3d){state->p.model.x[i], state->p.model.y[i], state->p.model.z[i]};
		p_world = point_trs_mult(p_mod, trs);

		state->p.world.x[i] = point_trs_mult(p_mod, trs);
		state->p.world.y[i] = point_trs_mult(p_mod, trs);
		state->p.world.z[i] = point_trs_mult(p_mod, trs);
		i++;
	}
}
