/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:24:58 by sancuta           #+#    #+#             */
/*   Updated: 2026/01/25 15:49:53 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stash
{
	ssize_t			len;
	ssize_t			offset;
	struct s_stash	*next;
	int				fd;
	char			content[BUFFER_SIZE + 1];
}	t_stash;

char	*get_next_line(int fd);

//	string utils
char	*ft_join(char *nl_buf, size_t *nl_len, t_stash *fd_buf, size_t to_cpy);
int		ft_make_next_line(char **next_line, size_t *nl_len, t_stash *buffer);

//	buffer-list utils
t_stash	*ft_bufnew(int fd);
t_stash	*ft_get_buffer_fd(t_stash **head, int fd);
int		ft_fill_buffer(t_stash *buffer);
void	ft_free_all(t_stash **head);
void	ft_free_buf(t_stash **head, int fd);
#endif
