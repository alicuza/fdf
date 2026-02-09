/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:05:02 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/09 21:13:51 by sancuta          ###   ########.fr       */
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

	i = 0;
	while ((*str_arr)[i])
	{
		free((*str_arr)[i]);
		i++;
	}
	free(*str_arr);
	*str_arr = NULL;
}

void	handle_exit(t_state *state, int exit_status, const char *caller)
{
	// mlx destroy functions
	// free everything allocated
	// close open fd
	// exit with message of where it failed
}
