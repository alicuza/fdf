/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:10:45 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/15 01:00:26 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_symbols(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	handle_edge_cases(char *res, int n)
{
	if (!n)
	{
		ft_strlcpy(res, "0", 2);
		return (1);
	}
	if (n == -2147483648)
	{
		ft_strlcpy(res, "-2147483648", 12);
		return (1);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	char		*res;
	size_t		len;

	len = count_symbols(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	if (handle_edge_cases(res, n))
		return (res);
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	res[len] = '\0';
	while (n)
	{
		len--;
		res[len] = (char)((n % 10) + 48);
		n /= 10;
	}
	return (res);
}
