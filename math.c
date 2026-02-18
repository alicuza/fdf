/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:34:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/18 09:01:01 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4	new_mat4_id(void)
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

t_mat4	new_mat_iso(void)
{
	t_mat4	res;

	res.pos[0] = M_SQRT1_2;
	res.pos[1] = -M_SQRT1_3;
	res.pos[2] = M_SQRT1_6;
	res.pos[3] = IMG_SIZE_X / 2.0;

	res.pos[4] = M_SQRT1_2;
	res.pos[5] = M_SQRT1_3;
	res.pos[6] = -M_SQRT1_6;
	res.pos[7] = IMG_SIZE_Y / 2.0;

	res.pos[8] = 0.0;
	res.pos[9] = M_SQRT1_3;
	res.pos[10] = M_SQRT2_3;
	res.pos[11] = 0.0;

	res.pos[12] = 0.0;
	res.pos[13] = 0.0;
	res.pos[14] = 0.0;
	res.pos[15] = 1.0;
	return (res);
}

t_mat4	new_mat_21(void)
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

void	p_soa_trs_mult_3d(t_fvec3d_arr *p0, t_fvec3d_arr *p1, size_t size, t_mat4 m)
{
	size_t		i;
	
	i = 0;
	while (i < size)
	{
		p1->x[i] = p0->x[i] * m.pos[0] + p0->y[i] * m.pos[1] + p0->z[i] * m.pos[2] + m.pos[3];
		p1->y[i] = p0->x[i] * m.pos[4] + p0->y[i] * m.pos[5] + p0->z[i] * m.pos[6] + m.pos[7];
		p1->z[i] = p0->x[i] * m.pos[8] + p0->y[i] * m.pos[9] + p0->z[i] * m.pos[10] + m.pos[11];
		i++;
	}
}

void	p_soa_trs_mult_2d(t_fvec3d_arr *p0, t_fvec2d_arr *p1, size_t size, t_mat4 m)
{
	size_t		i;
	
	i = 0;
	while (i < size)
	{
		p1->x[i] = p0->x[i] * m.pos[0] + p0->y[i] * m.pos[1] + p0->z[i] * m.pos[2] + m.pos[3];
		p1->y[i] = p0->x[i] * m.pos[4] + p0->y[i] * m.pos[5] + p0->z[i] * m.pos[6] + m.pos[7];
		i++;
	}
}

t_quat	new_quat_id(void)
{
	t_quat	res;

	res = (t_quat){1, 0, 0, 0};
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

t_fvec3d_arr	vec_soa_norm(t_fvec3d_arr v, size_t len)
{
	double			mag;
	double			mag_max;
	size_t			i;

	mag_max = 0.0;
	i = 0;
	while (i < len)
	{
		mag = sqrt(v.x[i] * v.x[i] + v.y[i] * v.y[i] + v.z[i] * v.z[i]);
		if (mag > mag_max)
			mag_max = mag;
		i++;
	}
	if (mag_max <= FLT_EPSILON) // if not enough, try DBL_EPSILON
		return (v);
	i = 0;
	while (i < len)
	{
		v.x[i] /= mag_max;
		v.y[i] /= mag_max;
		v.z[i] /= mag_max;
		i++;
	}
	return (v);
}

t_mat4	generate_trs_mat(t_fvec3d transform, t_quat q, double scale)
{
	t_mat4	res;

	res = new_mat4_id();
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
	return (fmod(deg, 360.0) * (M_PI / 180.0)); // precompute M_PI/180 or are there any macros?
}

double	rad_to_deg(double rad)
{
	return (fmod(rad, (2.0 * M_PI)) * (180.0 / M_PI)); // precompute 2*M_PI and 180/M_PI or are there any macros?
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

int	is_quat_equal(t_quat q1, t_quat q2) //TODO any error handling needed here?
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (((double *)&q1)[i] != ((double *)&q2)[i])
			return (0);
		i++;
	}
	return(1);
}

int	min(int n1, int n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

int	max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

