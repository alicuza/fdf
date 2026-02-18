/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:50:01 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/18 10:25:35 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_press(int keycode, void *param)
{
	t_state_data	*state;

	state = (t_state_data *)param;
	if (keycode == XK_Escape)
	{
		handle_exit((t_state_data *)param, EXIT_SUCCESS, "handle_key_press");
	}
	return (0);
}
