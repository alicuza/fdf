/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:14:20 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/27 09:43:38 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

inline static int	is_on_screen(t_dim2d img, int x, int y)
{
	return (x >= 0 && x < (int)img.width && y >= 0 && y < (int)img.height);
}

static void	draw_hline(t_state_data *state, unsigned int ind, t_vec2d delta,
		t_vec2d step)
{
	int		acc;
	int		i;
	t_vec2d	pix;

	pix.x = state->p.screen.x[ind];
	pix.y = state->p.screen.y[ind];
	acc = 0;
	i = 0;
	while (i < delta.x * step.x)
	{
		if (is_on_screen(state->img.dim, pix.x, pix.y))
			put_pixel(state, pix.x, pix.y, 0x00ffffff);
		pix.x += step.x;
		acc += 2 * delta.y * step.y;
		if (acc > delta.x * step.x)
		{
			pix.y += step.y;
			acc -= 2 * delta.x * step.x;
		}
		i++;
	}
}

static void	draw_vline(t_state_data *state, unsigned int ind, t_vec2d delta,
		t_vec2d step)
{
	int		acc;
	int		i;
	t_vec2d	pix;

	pix.x = state->p.screen.x[ind];
	pix.y = state->p.screen.y[ind];
	acc = 0;
	i = 0;
	while (i < delta.y * step.y)
	{
		if (is_on_screen(state->img.dim, pix.x, pix.y))
			put_pixel(state, pix.x, pix.y, 0x00ffffff);
		pix.y += step.y;
		acc += 2 * delta.x * step.x;
		if (acc > delta.y * step.y)
		{
			pix.x += step.x;
			acc -= 2 * delta.y * step.y;
		}
		i++;
	}
}

static void	make_line(t_state_data *state, unsigned int ind1, unsigned int ind2)
{
	t_vec2d	delta;
	t_vec2d	sign;

	sign = (t_vec2d){0};
	delta.x = state->p.screen.x[ind2] - state->p.screen.x[ind1];
	if (delta.x < 0)
		sign.x = -1;
	else if (delta.x > 0)
		sign.x = 1;
	delta.y = state->p.screen.y[ind2] - state->p.screen.y[ind1];
	if (delta.y < 0)
		sign.y = -1;
	else if (delta.y > 0)
		sign.y = 1;
	if (delta.x * sign.x >= delta.y * sign.y)
		draw_hline(state, ind1, delta, sign);
	else
		draw_vline(state, ind1, delta, sign);
}

void	draw(t_state_data *state)
{
	size_t	i;

	ft_memset(state->img.buf, 0, state->img.size);
	i = 0;
	while (i < state->map.size)
	{
		if (i % state->map.dim.width + 1 < state->map.dim.width
			&& !both_off_screen(state, i, i + 1))
			make_line(state, i, i + 1);
		if (i / state->map.dim.width + 1 < state->map.dim.height
			&& !both_off_screen(state, i, i + state->map.dim.width))
			make_line(state, i, i + state->map.dim.width);
		i++;
	}
	if (is_on_screen(state->img.dim, state->p.screen.x[i - 1],
			state->p.screen.y[i - 1]))
		put_pixel(state, state->p.screen.x[i - 1], state->p.screen.y[i - 1],
			get_color(state->p.model.z[i - 1]));
	mlx_put_image_to_window(state->mlx_ptr, state->win.ptr,
		state->img.ptr, state->img.offset_to_win.x,
		state->img.offset_to_win.y);
}
