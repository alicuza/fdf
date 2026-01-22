/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:48:25 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/23 16:29:28 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

t_stash	*ft_bufnew(int fd)
{
	t_stash	*new;

	new = malloc(sizeof(t_stash));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->len = read(fd, new->content, BUFFER_SIZE);
	if (new->len <= 0)
		return (free(new), NULL);
	new->offset = 0;
	new->content[new->len] = '\0';
	new->next = NULL;
	return (new);
}

char	*ft_join(char *nl_buf, size_t *nl_len, t_stash *fd_buf, size_t to_cpy)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	tmp = malloc(*nl_len + to_cpy + 1);
	if (!tmp)
		return (free(nl_buf), NULL);
	i = 0;
	while (i < *nl_len)
	{
		tmp[i] = nl_buf[i];
		i++;
	}
	j = 0;
	while (j < to_cpy)
	{
		tmp[i + j] = fd_buf->content[fd_buf->offset];
		j++;
		fd_buf->offset++;
	}
	*nl_len += to_cpy;
	tmp[*nl_len] = '\0';
	return (free(nl_buf), tmp);
}

void	ft_free_all(t_stash **head)
{
	t_stash	*buffer;
	t_stash	*tmp;

	buffer = *head;
	while (buffer)
	{
		tmp = buffer->next;
		free(buffer);
		buffer = tmp;
	}
	(*head)->next = NULL;
}

void	ft_free_buf(t_stash **head, int fd)
{
	t_stash	*current;
	t_stash	*previous;

	current = *head;
	previous = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (!previous)
				*head = current->next;
			else
				previous->next = current->next;
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}
