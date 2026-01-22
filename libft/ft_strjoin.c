/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:58:40 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/13 18:17:08 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	len;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	total_len = len + ft_strlen(s2);
	res = malloc(total_len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, total_len + 1);
	ft_strlcat(res, s2, total_len + 1);
	return (res);
}
