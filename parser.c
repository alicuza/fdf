/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:18:31 by sancuta           #+#    #+#             */
/*   Updated: 2026/02/03 13:03:45 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	arr_width(char **str_arr);
int	arr_height(const char *path);
t_point	**on_alloc_fail_free_tpoint_arr(t_point **arr, size_t ind);

t_map parse(const char *path, t_point ***p)
{
	char	*cur_line;
	char	**split_line;
	int		fd;
	int		i;
	int		j;
	t_map		ret;
	
	ret = (t_map){0};
	fd = open(path, O_RDONLY);
	cur_line = get_next_line(fd);
	ret.height = arr_height(path);
	*p = malloc((ret.height + 2) * sizeof(t_point *));
	if (!p)
	{
		perror("t_point **parse, malloc failure");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (cur_line)
	{
		split_line = ft_split(cur_line, ' ');
		if (!ret.width)
			ret.width = arr_width(split_line);
		else if (ret.width != arr_width(split_line))
		{
			on_alloc_fail_free_tpoint_arr(*p, i);
			free(p);
			perror("t_point **parse, width of t_map not constant");
			exit(EXIT_FAILURE);
		}
		(*p)[i] = malloc((ret.width + 1) * sizeof(t_point));
		if (!(*p)[i])
		{
			on_alloc_fail_free_tpoint_arr(*p, i);
			free(*p);
			perror("t_point **parse, malloc failure 1 deep");
			exit(EXIT_FAILURE);
		}
		j = 0;
		while (split_line[j])
		{
			(*p)[i][j].x = j;
			(*p)[i][j].y = i;
			(*p)[i][j].z = ft_atoi(split_line[j]);
			j++;
		}
		cur_line = get_next_line(fd);
		i++;
	}
	return (close(fd), ret);
}
/*
int	parse_line(char *line, t_point *p)
{
	char	**split_line;

	split_line = ft_split(cur_line, ' ');
	p[i] = malloc(arr_width(split_line) * sizeof(int) + 1);
	j = 0;
	while (split_line[i])
	{
		p[i][j].x = j;
		p[i][j].y = i;
		p[i][j].z = ft_atoi(split_line[i]);
		j++;
	}
	cur_line = get_next_line(fd);
	p++;
	i++;
}
*/
int	arr_width(char **str_arr)
{
	int i;

	i = 0;
	while (str_arr[i] && *(str_arr[i]))
		i++;
	return (i);
}

int	arr_height(const char *path)
{
	int	i;
	int	fd;

	fd = open(path, O_RDONLY);
	i = 0;
	while (get_next_line(fd))
		i++;
	close(fd);
	return (i);
}

t_point	**on_alloc_fail_free_tpoint_arr(t_point **arr, size_t ind)
{
	while (ind-- > 0)
		free(arr[ind]);
	free(arr);
	return (NULL);
}
