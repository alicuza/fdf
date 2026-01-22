/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_form_spec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:52:35 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/14 06:16:10 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	ft_get_flags(const char **s, const char *mask_set);
static int			ft_get_precision(const char **s);
static int			ft_get_conv_spec(const char **s);

t_form_spec	ft_get_form_spec(const char **s, const char *mask_set)
{
	t_form_spec	res;

	res = (t_form_spec){0};
	res.precision = -1;
	res.flag = ft_get_flags(s, mask_set);
	res.field_width = ft_get_nbr(s);
	res.precision = ft_get_precision(s);
	if (res.precision != -1)
		res.flag = (res.flag | FLAG_DOT) & ~FLAG_ZERO;
	res.conv_spec = ft_get_conv_spec(s);
	if (res.conv_spec != -1)
		res.flag &= g_allowed_flags[ft_indchr(g_valid_conv_spec,
				res.conv_spec)];
	return (res);
}

static int	ft_get_precision(const char **s)
{
	int	precision;

	precision = -1;
	if (**s == '.')
	{
		(*s)++;
		precision = ft_get_nbr(s);
	}
	return (precision);
}

static unsigned int	ft_get_flags(const char **s, const char *mask_set)
{
	int				i;
	unsigned int	flag;

	flag = 0;
	i = ft_indchr(mask_set, **s);
	while (i != -1)
	{
		flag |= (1 << i);
		(*s)++;
		i = ft_indchr(mask_set, **s);
	}
	return (flag);
}

static int	ft_get_conv_spec(const char **s)
{
	int	conv_spec;

	if (ft_indchr(g_valid_conv_spec, **s) != -1)
	{
		conv_spec = **s;
		(*s)++;
	}
	else
		conv_spec = -1;
	return (conv_spec);
}
