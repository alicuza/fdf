/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_nbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:45:54 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/18 16:14:16 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	recurse(unsigned long n, const char *base,
				unsigned long base_len, int i);

int	ft_put_nbr_base(unsigned long n, const char *base)
{
	unsigned long	base_len;

	base_len = ft_strlen(base);
	return (recurse(n, base, base_len, 0));
}

static int	recurse(unsigned long n, const char *base,
				unsigned long base_len, int i)
{
	int	written;

	if (n >= base_len)
	{
		written = recurse(n / base_len, base, base_len, i);
		if (written < 0)
			return (-1);
		i = written;
	}
	written = ft_putchar(base[n % base_len]);
	if (written < 0)
		return (-1);
	return (i + written);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}
