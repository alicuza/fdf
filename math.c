/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:34:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/16 13:37:30 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_mat4	mat4_mult(t_mat4 m1, t_mat4 m2)
{
	int	i;
	int	j;
	int	k;
	t_mat4	res;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			res.pos[i + 4 * j] = 0;
			k = 0;
			while (k < 4)
			{
				res.pos[i + 4 * j] += m1.pos[i + 4 * k] * m2.pos[k + 4 * j];
				k++;
			}
			i++;
		}
		j++;
	}
	return (res);
}

t_fvec3d	point_trs_mult(t_fvec3d p, t_mat4 m)
{
	t_fvec3d	res;

	res.x = p.x * m.pos[0] + p.y * m.pos[1] + p.z * m.pos[2] + m.pos[3];
	res.y = p.x * m.pos[4] + p.y * m.pos[5] + p.z * m.pos[6] + m.pos[7];
	res.z = p.x * m.pos[8] + p.y * m.pos[9] + p.z * m.pos[10] + m.pos[11];
	return (res);
}

t_quat	quat_mult(t_quat q1, t_quat q2)
{
	t_quat	res;

	res.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	res.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	res.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	res.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (res);
}

t_quat	quat_norm(t_quat q)
{
	double	mag;
	t_quat	res;

	res = (t_quat){1, 0, 0, 0};
	mag = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	if (mag <= FLT_EPSILON) // if not enough, try DBL_EPSILON
		return (res);
	res.w = q.w / mag;
	res.x = q.x / mag;
	res.y = q.y / mag;
	res.z = q.z / mag;
	return (res);
}

t_fvec3d	vec_norm(t_fvec3d v)
{
	double		mag;
	t_fvec3d	res;

	res = (t_fvec3d){0, 0, 0};
	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (mag <= FLT_EPSILON) // if not enough, try DBL_EPSILON
		return (res);
	res.x = v.x / mag;
	res.y = v.y / mag;
	res.z = v.z / mag;
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

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}

double	rad_to_deg(double rad)
{
	return (rad * (180 / M_PI));
}

t_quat	quat_from_aa(double rad, t_fvec3d axis)
{
	t_quat	res;
	double	sin_rad_half;

	axis = vec_norm(axis);
	sin_rad_half = sin(rad / 2.0);
	res.w = cos(rad / 2.0);
	res.x = axis.x * sin_rad_half;
	res.y = axis.y * sin_rad_half;
	res.z = axis.z * sin_rad_half;

	return (res);
}


