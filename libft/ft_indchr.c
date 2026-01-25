/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:44:56 by sancuta           #+#    #+#             */
/*   Updated: 2026/01/25 15:59:15 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_indchr(const char *s, int c)
{
	ssize_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return (i);
	return (-1);
}
