/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:38:01 by sancuta           #+#    #+#             */
/*   Updated: 2026/01/25 15:47:12 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_nbr(const char **s)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(**s))
	{
		ret *= 10;
		ret += **s - 48;
		(*s)++;
	}
	return (ret);
}

int	ft_abs_nbr_len(unsigned long n, unsigned long base)
{
	int	i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}
