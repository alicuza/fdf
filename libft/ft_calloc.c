/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:39:35 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/24 12:13:27 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>


void    *ft_calloc(size_t nmemb, size_t size)
{
    char    *ptr;

    if (!nmemb || !size)
        return (malloc(0));
    if (nmemb && size > LLONG_MAX / nmemb)
        return (0);
    ptr = malloc(size * nmemb);
    if (!ptr || !nmemb)
        return (ptr);
    ft_bzero(ptr, nmemb * size);
    return (ptr);
}
/*void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	total_size;

	if (!nmemb || !size)
	{
		return (malloc(0));
	}
	if (SIZE_MAX / size <= nmemb)
	{
		return (NULL);
	}
	total_size = nmemb * size;
	res = malloc(total_size);
	if (!res)
		return (NULL);
	ft_bzero(res, total_size);
	return (res);
}*/
