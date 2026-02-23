/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:14:20 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/23 07:05:59 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_on_screen(t_state_data *state, size_t i);

void	draw(t_state_data *state)
{
	size_t	ind;
	size_t	i;

	ft_memset(state->img.buf, 0, state->img.size);
	i = 0;
	while (i < state->map.size)
	{
		ind = (int)state->p.screen.y[i] * state->img.size_line
			+ (int)state->p.screen.x[i] * state->img.bits_ppix / 8;
		if (is_on_screen(state, i))
			*(unsigned int *)(state->img.buf + ind) = 0x00ffffff;
//		draw_line(state, i);
		i++;
	}
	mlx_put_image_to_window (state->mlx_ptr, state->win.ptr,
		state->img.ptr, state->img.offset_to_win.x,
		state->img.offset_to_win.y);
}

static int	is_on_screen(t_state_data *state, size_t ind)
{
	return (state->p.screen.x[ind] >= 0
		&& state->p.screen.x[ind] < state->img.dim.width
		&& state->p.screen.y[ind] >= 0
		&& state->p.screen.y[ind] < state->img.dim.height);
}
/*
static t_fvec2d get_step(t_fvec2d_arr p, size_t ind1, size_t ind2);
{
	t_fvec2d	dim;
	t_fvec2d	step;

	dim.x = p.x[ind2] - p.x[ind1];
	dim.y = p.y[ind2] - p.y[ind1];
	if (dim.y < EPSILON)
		step = (t_fvec2d){1.0, 0.0};
	else if (dim.x < EPSILON)
		step = (t_fvec2d){0.0, 1.0};
	else if (dim.x - dim.y < EPSILON)
		step = (t_fvec2d){1.0, 1.0};
	else
	{
		step.x = dim.y / dim.x;
		step.y = dim.x / dim.y;
	}
	return (step);
}

static void	draw_line(t_state_data *state, size_t ind)
{
	t_fvec2d	step;

	step = get_step(state->p.screen, ind, ind + 1);
	if (step.x > 1.0)
		draw_hline();
	else
		draw_vline();
	step = get_step(state->p.screen, ind, ind + state->map.dim.width);
	if (step.x > 1.0)
		draw_hline();
	else
		draw_vline();
}
*/
