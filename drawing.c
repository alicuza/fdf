/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:14:20 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/18 17:02:55 by sancuta          ###   ########.fr       */
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
		i++;
	}
	mlx_put_image_to_window (state->mlx_ptr, state->win.ptr,
		state->img.ptr, state->img.offset_to_win.x,
		state->img.offset_to_win.y);
}

static int	is_on_screen(t_state_data *state, size_t i)
{
	return (state->p.screen.x[i] >= 0
		&& state->p.screen.x[i] < state->img.dim.width
		&& state->p.screen.y[i] >= 0
		&& state->p.screen.y[i] < state->img.dim.height);
}
