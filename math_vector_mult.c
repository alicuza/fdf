/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector_mult.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:34:36 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/23 13:00:36 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4	mat4_mult(t_mat4 m1, t_mat4 m2)
{
	int		i;
	int		j;
	int		k;
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

void	p_soa_trs_mult_3d(t_fvec3d_arr *p0, t_fvec3d_arr *p1, size_t size,
		t_mat4 m)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		p1->x[i] = p0->x[i] * m.pos[0] + p0->y[i] * m.pos[1]
			+ p0->z[i] * m.pos[2] + m.pos[3];
		p1->y[i] = p0->x[i] * m.pos[4] + p0->y[i] * m.pos[5]
			+ p0->z[i] * m.pos[6] + m.pos[7];
		p1->z[i] = p0->x[i] * m.pos[8] + p0->y[i] * m.pos[9]
			+ p0->z[i] * m.pos[10] + m.pos[11];
		i++;
	}
}

void	p_soa_trs_mult_2d(t_fvec3d_arr *p0, t_vec2d_arr *p1, size_t size,
		t_mat4 m)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		p1->x[i] = (int)round(p0->x[i] * m.pos[0] + p0->y[i] * m.pos[1]
			+ p0->z[i] * m.pos[2] + m.pos[3]);
		p1->y[i] = (int)round(p0->x[i] * m.pos[4] + p0->y[i] * m.pos[5]
			+ p0->z[i] * m.pos[6] + m.pos[7]);
		i++;
	}
}

t_fvec3d	vec_norm(t_fvec3d v)
{
	double		mag;
	t_fvec3d	res;

	res = (t_fvec3d){0, 0, 0};
	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (mag <= EPSILON)
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
	if (mag_max <= EPSILON)
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
