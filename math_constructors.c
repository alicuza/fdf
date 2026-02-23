/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_constructors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:34:18 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/23 12:33:21 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_quat	quat_id(void)
{
	t_quat	res;

	res = (t_quat){1, 0, 0, 0};
	return (res);
}

t_mat4	mat4_id(void)
{
	t_mat4	res;

	res.pos[0] = 1.0;
	res.pos[1] = 0.0;
	res.pos[2] = 0.0;
	res.pos[3] = 0.0;
	res.pos[4] = 0.0;
	res.pos[5] = 1.0;
	res.pos[6] = 0.0;
	res.pos[7] = 0.0;
	res.pos[8] = 0.0;
	res.pos[9] = 0.0;
	res.pos[10] = 1.0;
	res.pos[11] = 0.0;
	res.pos[12] = 0.0;
	res.pos[13] = 0.0;
	res.pos[14] = 0.0;
	res.pos[15] = 1.0;
	return (res);
}

t_mat4	mat_iso(void)
{
	t_mat4	res;

	res.pos[0] = M_SQRT1_2;
	res.pos[1] = -M_SQRT1_2;
	res.pos[2] = 0.0;
	res.pos[3] = IMG_SIZE_X / 2.0;
	res.pos[4] = M_SQRT1_6;
	res.pos[5] = M_SQRT1_6;
	res.pos[6] = -M_SQRT2_3;
	res.pos[7] = IMG_SIZE_Y / 2.0;
	res.pos[8] = M_SQRT1_3;
	res.pos[9] = M_SQRT1_3;
	res.pos[10] = M_SQRT2_3;
	res.pos[11] = 0.0;
	res.pos[12] = 0.0;
	res.pos[13] = 0.0;
	res.pos[14] = 0.0;
	res.pos[15] = 1.0;
	return (res);
}

t_mat4	mat_21(void)
{
	t_mat4	res;

	res.pos[0] = M_SQRT3_HALF;
	res.pos[1] = -M_SQRT3_HALF;
	res.pos[2] = 0.0;
	res.pos[3] = IMG_SIZE_X / 2.0;
	res.pos[4] = 0.5;
	res.pos[5] = 0.5;
	res.pos[6] = -1.0;
	res.pos[7] = IMG_SIZE_Y / 2.0;
	res.pos[8] = 0.0;
	res.pos[9] = 0.0;
	res.pos[10] = 1.0;
	res.pos[11] = 0.0;
	res.pos[12] = 0.0;
	res.pos[13] = 0.0;
	res.pos[14] = 0.0;
	res.pos[15] = 1.0;
	return (res);
}

t_mat4	generate_trs_mat(t_fvec3d transform, t_quat q, double scale)
{
	t_mat4	res;

	res = mat4_id();
	res.pos[0] = (1.0 - 2.0 * (q.y * q.y + q.z * q.z)) * scale;
	res.pos[1] = (2.0 * (q.x * q.y - q.z * q.w)) * scale;
	res.pos[2] = (2.0 * (q.x * q.z + q.y * q.w)) * scale;
	res.pos[3] = transform.x;
	res.pos[4] = (2.0 * (q.x * q.y + q.z * q.w)) * scale;
	res.pos[5] = (1.0 - 2.0 * (q.x * q.x + q.z * q.z)) * scale;
	res.pos[6] = (2.0 * (q.y * q.z - q.x * q.w)) * scale;
	res.pos[7] = transform.y;
	res.pos[8] = (2.0 * (q.x * q.z - q.y * q.w)) * scale;
	res.pos[9] = (2.0 * (q.y * q.z + q.x * q.w)) * scale;
	res.pos[10] = (1.0 - 2.0 * (q.x * q.x + q.y * q.y)) * scale;
	res.pos[11] = transform.z;
	res.pos[12] = 0.0;
	res.pos[13] = 0.0;
	res.pos[14] = 0.0;
	res.pos[15] = 1.0;
	return (res);
}
