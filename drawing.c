/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:14:20 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/23 10:00:14 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

inline static int	is_on_screen(t_dim2d img, t_vec2d pix);
//inline static void	draw_point(t_state_data * state, unsigned int ind);
//inline static unsigned int	get_color(double z);
static void	make_line(t_state_data *state, unsigned int ind1,
		unsigned int ind2);
static void	draw_hline(t_state_data *state, unsigned int ind, t_vec2d delta,
		t_vec2d step);
inline static void	put_pixel(t_state_data *state, int x, int y,
		unsigned int color);

void	draw(t_state_data *state)
{
	size_t	i;

	ft_memset(state->img.buf, 0, state->img.size);
	i = 0;
	while (i < state->map.size)
	{
//		if (is_on_screen(state->img.dim, state->p.screen.x, state->p.screen.y))
//			draw_point(state, i);
		if (i + 1 < state->map.size)
			make_line(state, i, i + 1);
		if (i + state->map.dim.width < state->map.size)
			make_line(state, i, i + state->map.dim.width);
		i++;
	}
	mlx_put_image_to_window(state->mlx_ptr, state->win.ptr,
		state->img.ptr, state->img.offset_to_win.x,
		state->img.offset_to_win.y);
}

inline static int	is_on_screen(t_dim2d img, t_vec2d pix)
{
	return (pix.x >= 0 && pix.x < img.width
		&& pix.y >= 0 && pix.y < img.height);
}

static void	make_line(t_state_data *state, unsigned int ind1,
		unsigned int ind2)
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
//	else
//		draw_vline(state, ind1, delta, sign);
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
	while (i < delta.x)
	{
		pix.x += step.x;
		acc += 2 * delta.x;
		if (acc > delta.y)
		{
			pix.y += step.y;
			if (is_on_screen(state->img.dim, pix))
			put_pixel(state, pix.x, pix.y, 0x00ffffff);
			acc -= delta.y;
		}
		i++;
	}
}
/*
static void	draw_vline(t_state_data *state, int ind, int delta, int step_x, int step_y)
{
	int	acc
	int	i;

	acc = 0;
	i = 0;
	while (i < range)
	{
		state->p.screen.y += step_y;
		acc += 2 * delta_x;
		if (acc > delta_y)
			state->p.screen.x += step_x;
		i++;
	}
}

inline static void	draw_point(t_state_data * state, unsigned int ind)
{
	int	i;

	i = state->p.screen.y[ind] * state->img.size_line
		+ state->p.screen.x[ind] * state->img.bits_ppix / 8;
	put_pixel(state, i, get_color(state->p.model.z[ind]));
}

inline static unsigned int	get_color(double z)
{
	(void)z;
	return (0x00ffffff);
}
*/
inline static void put_pixel(t_state_data *state, int x, int y,
		unsigned int color)
{
	int	i;

	i = y * state->img.size_line + x * state->img.bits_ppix / 8;
	*(unsigned int *)(state->img.buf + i) = color;
}
