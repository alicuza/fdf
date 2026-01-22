/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:23:08 by sancuta           #+#    #+#             */
/*   Updated: 2025/11/22 18:36:48 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_stash	*head;
	t_stash			*buffer;
	char			*next_line;
	size_t			nl_len;
	int				status;

	if (fd == -255)
		return (ft_free_all(&head), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_get_buffer_fd(&head, fd);
	if (!buffer)
		return (NULL);
	next_line = NULL;
	nl_len = 0;
	status = ft_make_next_line(&next_line, &nl_len, buffer);
	if (status == -1)
		return (ft_free_buf(&head, fd), free(next_line), NULL);
	if (status == 0)
	{
		ft_free_buf(&head, fd);
		if (nl_len == 0)
			return (free(next_line), NULL);
	}
	return (next_line);
}

t_stash	*ft_get_buffer_fd(t_stash **head, int fd)
{
	t_stash	*buffer;

	if (!(*head))
	{
		*head = ft_bufnew(fd);
		if (!(*head))
			return (NULL);
		return (*head);
	}
	buffer = *head;
	while (buffer)
	{
		if (buffer->fd == fd)
			return (buffer);
		if (!buffer->next)
		{
			buffer->next = ft_bufnew(fd);
			if (!buffer->next)
				return (NULL);
			return (buffer->next);
		}
		buffer = buffer->next;
	}
	return (NULL);
}

/*	return can be:
	-1 ... error: malloc / read
	0 ... EOF -> clean up the buffer
	1 ... success
 */
int	ft_make_next_line(char **next_line, size_t *nl_len, t_stash *buffer)
{
	ssize_t	nl_ind;
	int		buffer_status;

	while (1)
	{
		nl_ind = ft_indchr(buffer->content + buffer->offset, '\n');
		if (nl_ind != -1)
		{
			*next_line = ft_join(*next_line, nl_len, buffer, nl_ind + 1);
			if (!*next_line)
				return (-1);
			return (1);
		}
		*next_line = ft_join(*next_line, nl_len,
				buffer, buffer->len - buffer->offset);
		if (!*next_line)
			return (-1);
		buffer_status = ft_fill_buffer(buffer);
		if (buffer_status == -1)
			return (buffer_status);
		if (buffer_status == 0)
			return (*nl_len > 0);
	}
}

/*	return can be:
	-1 ... read error
	0 ... EOF reached
	1 ... success
 */
int	ft_fill_buffer(t_stash *buffer)
{
	if (buffer->len > 0 && buffer->len > buffer->offset)
		return (1);
	buffer->len = read(buffer->fd, buffer->content, BUFFER_SIZE);
	buffer->offset = 0;
	if (buffer->len < 1)
	{
		buffer->content[0] = '\0';
		return (buffer->len);
	}
	buffer->content[buffer->len] = '\0';
	return (1);
}
