/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:05:02 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/23 23:20:35 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}

void	free_str_arr(char ***str_arr)
{
	size_t	i;

	if (!(str_arr && *str_arr))
		return ;
	i = 0;
	while ((*str_arr)[i])
	{
		free((*str_arr)[i]);
		i++;
	}
	free(*str_arr);
	*str_arr = NULL;
}

void	free_points(t_state_data *state)
{
	free(state->p.model.x);
	free(state->p.model.y);
	free(state->p.model.z);
	free(state->p.world.x);
	free(state->p.world.y);
	free(state->p.world.z);
	free(state->p.screen.x);
	free(state->p.screen.y);
}

void	handle_exit(t_state_data *state, int exit_status, const char *caller)
{
	if (state->img.ptr)
		mlx_destroy_image (state->mlx_ptr, state->img.ptr);
	if (state->win.ptr)
		mlx_destroy_window(state->mlx_ptr, state->win.ptr);
	if (state->mlx_ptr)
	{
		mlx_loop_end(state->mlx_ptr);
		mlx_destroy_display(state->mlx_ptr);
		free(state->mlx_ptr);
	}
	free_points(state);
	if (state->fd != -1)
		close(state->fd);
	free_str(&(state->gnl_line));
	free_str_arr(&(state->split_line));
	get_next_line(-255);
	if (exit_status == EXIT_FAILURE)
		perror(caller);
	exit(exit_status);
}

int	call_exit(void *data)
{
	t_state_data	*state;

	state = (t_state_data *)data;
	handle_exit(state, EXIT_SUCCESS, "call_exit");
	return (1);
}
