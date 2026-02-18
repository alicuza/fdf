/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_quaternions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:36:48 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/18 17:37:53 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	res = quat_id();
	mag = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	if (mag <= EPSILON)
		return (res);
	res.w = q.w / mag;
	res.x = q.x / mag;
	res.y = q.y / mag;
	res.z = q.z / mag;
	return (res);
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
