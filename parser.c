/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:18:31 by sancuta           #+#    #+#             */
/*   Updated: 2026/01/22 19:19:57 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

t_point	*parse(const char *path)
{
	t_point	*p;
	char	*cur_line;
	char	**split_line;
	int		fd;
	int		i;
	int		j;
	
	fd = open(path, O_RDONLY);
	cur_line = get_next_line(fd);
	i = 0;
	while (cur_line)
	{
		split_line = ft_split(cur_line, ' ');
		p = malloc(arrlen(split_line) * sizeof(int) + 1);
		j = 0;
		while (split_line[i])
		{
			p->x = j;
			p->y = i;
			p->z = ft_atoi(split_line[i]);
			j++;
		}
		cur_line = get_next_line(fd);
		i++;
	}
	return (close(fd), p);
}

int	arrlen(char **str_arr)
{
	int i;

	i = 0;
	while (*str_arr)
	{
		str_arr[i];
		i++;
	}
	return (i);
}

