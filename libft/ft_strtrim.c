/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:11:35 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/13 21:04:12 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_front_trim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	start;

	start = 0;
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				start = i + 1;
				break ;
			}
			j++;
		}
		i++;
		if (start != i)
			break ;
	}
	return (start);
}

static size_t	ft_back_trim(const char *s1, const char *set, size_t start)
{
	size_t	i;
	size_t	j;
	size_t	end;

	end = ft_strlen(s1) - 1;
	i = end;
	while (i > start)
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				end = i - 1;
				break ;
			}
			j++;
		}
		i--;
		if (end != i)
			break ;
	}
	return (end - start + 1);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	len;
	size_t	start;

	if (!s1 || !set)
		return (NULL);
	start = ft_front_trim(s1, set);
	len = ft_back_trim(s1, set, start);
	return (ft_substr(s1, start, len));
}
