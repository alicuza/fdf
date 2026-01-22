/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:56:38 by sancuta           #+#    #+#             */
/*   Updated: 2025/10/20 18:40:17 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*head;
	void	*tmp;

	if (!(lst && f && del))
		return (NULL);
	head = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		map = ft_lstnew(tmp);
		if (!map)
		{
			ft_lstclear(&head, del);
			del(tmp);
			return (NULL);
		}
		ft_lstadd_back(&head, map);
		lst = lst->next;
	}
	return (head);
}
