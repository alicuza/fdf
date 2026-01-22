/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:49:33 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/14 17:58:18 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_form_spec_handler(t_form_spec *data, int flag, const char **s,
		va_list *args)
{
	if (flag == -1)
		return (-1);
	if (!flag)
		return (ft_putchar(*(*s)++));
	else
	{
		*data = ft_get_form_spec(s, g_valid_flags);
		if (data->conv_spec == -1)
			return (-1);
		return (ft_prt_arg(data, args));
	}
}

int	ft_check_form_spec(const char **s)
{
	if (**s == '%')
	{
		(*s)++;
		if (!(**s))
			return (-1);
		if (**s == '%')
			return (0);
		return (1);
	}
	return (0);
}
