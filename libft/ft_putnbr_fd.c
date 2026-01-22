/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 01:14:48 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/16 16:46:59 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	size_t	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	handle_edge_cases(int n, int fd)
{
	if (!n)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return (1);
	}
	return (0);
}

static void	make_powers_of_ten(size_t *ten_to_pow)
{
	size_t	i;

	ten_to_pow[0] = 1;
	i = 1;
	while (i < 11)
	{
		ten_to_pow[i] = ten_to_pow[i - 1] * 10;
		i++;
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	i;
	size_t	len;
	size_t	ten_to_pow[11];

	len = count_digits(n);
	if (handle_edge_cases(n, fd))
		return ;
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	make_powers_of_ten(ten_to_pow);
	i = 0;
	while (i < len)
	{
		ft_putchar_fd(n / ten_to_pow[len - i - 1] + '0', fd);
		n %= ten_to_pow[len - i - 1];
		i++;
	}
	return ;
}
