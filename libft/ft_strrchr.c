/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:38:25 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/20 15:56:38 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;

	size = ft_strlen(s);
	while (size > 0)
	{
		if ((unsigned char)s[size] == (unsigned char)c)
			return ((char *)s + size);
		size--;
	}
	if ((unsigned char)s[size] == (unsigned char)c)
		return ((char *)s + size);
	return (NULL);
}
