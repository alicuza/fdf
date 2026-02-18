/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:19:28 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/18 15:51:54 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

/*	pay attention to the wording in strtol(3):
		"The  string  may  begin  with an arbitrary amount of
		white space (as determined by isspace(3)) followed by
		a single optional '+' or '-' sign.
	only **one** sign check is needed!*/

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		res;

	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (ft_issign(nptr[i]))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		res = res * 10 + sign * (nptr[i] - 48);
		i++;
	}
	return (res);
}
