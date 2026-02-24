/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:50:01 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/24 19:00:06 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	keycode_to_move(int keycode)
{
	if (keycode == XK_w)
		return (MOVE_XP);
	if (keycode == XK_s)
		return (MOVE_XN);
	if (keycode == XK_a)
		return (MOVE_YP);
	if (keycode == XK_d)
		return (MOVE_YN);
	if (keycode == XK_q)
		return (MOVE_ZP);
	if (keycode == XK_e)
		return (MOVE_ZN);
	return (-1);
}

static int	keycode_to_rot(int keycode)
{
	if (keycode == XK_i)
		return (ROT_YP);
	if (keycode == XK_k)
		return (ROT_YN);
	if (keycode == XK_u)
		return (ROT_XP);
	if (keycode == XK_o)
		return (ROT_XN);
	if (keycode == XK_j)
		return (ROT_ZP);
	if (keycode == XK_l)
		return (ROT_ZN);
	return (-1);
}

static int	keycode_to_zoom(int keycode)
{
	if (keycode == XK_equal)
		return (ZOOM_IN);
	if (keycode == XK_minus)
		return (ZOOM_OUT);
	return (-1);
}

int	keycode_to_command(int keycode)
{
	int	cmd;

	cmd = keycode_to_move(keycode);
	if (cmd != -1)
		return (cmd);
	cmd = keycode_to_rot(keycode);
	if (cmd != -1)
		return (cmd);
	return (keycode_to_zoom(keycode));
}
