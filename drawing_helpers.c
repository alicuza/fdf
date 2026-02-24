/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 19:04:26 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/24 19:50:37 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	get_color(double z)
{
	(void)z;
	return (0x00ffffff);
}

void	put_pixel(t_state_data *state, int x, int y,
		unsigned int color)
{
	int	i;

	i = y * state->img.size_line + x * state->img.bits_ppix / 8;
	*(unsigned int *)(state->img.buf + i) = color;
}

int	both_off_screen(t_state_data *state, unsigned int ind1,
		unsigned int ind2)
{
	return ((state->p.screen.x[ind1] < 0 && state->p.screen.x[ind2] < 0)
		|| (state->p.screen.x[ind1] >= (int)state->img.dim.width
			&& state->p.screen.x[ind2] >= (int)state->img.dim.width)
		|| (state->p.screen.y[ind1] < 0 && state->p.screen.y[ind2] < 0)
		|| (state->p.screen.y[ind1] >= (int)state->img.dim.height
			&& state->p.screen.y[ind2] >= (int)state->img.dim.height));
}
