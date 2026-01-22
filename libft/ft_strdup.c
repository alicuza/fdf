/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:49:45 by sancuta           #+#    #+#             */
/*   Updated: 2025/09/30 09:41:32 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dst;

	size = ft_strlen(s) + 1;
	dst = malloc(size);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s, size);
	return (dst);
}
