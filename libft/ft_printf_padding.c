/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 02:41:41 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/14 06:00:04 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_space(t_form_spec *data, int arg_len, int sign_len)
{
	int	i;
	int	len;
	int	written;

	len = sign_len;
	if (data->conv_spec == 's')
	{
		if ((data->precision != -1) && (arg_len > data->precision))
			arg_len = data->precision;
	}
	else if ((data->precision != -1) && (arg_len < data->precision))
		arg_len = data->precision;
	len += arg_len;
	i = data->field_width - len;
	if (i <= 0)
		return (0);
	while (i > 0)
	{
		written = write(1, " ", 1);
		if (written < 0)
			return (-1);
		i--;
	}
	return (data->field_width - len);
}

int	ft_put_sign(t_form_spec *data)
{
	if ((data->flag & FLAG_HASH))
	{
		if (data->conv_spec == 'X')
			return (write(1, "0X", 2));
		else
			return (write(1, "0x", 2));
	}
	else if (data->flag & FLAG_NEG)
		return (write(1, "-", 1));
	else if (data->flag & FLAG_PLUS)
		return (write(1, "+", 1));
	else if (data->flag & FLAG_SPACE)
		return (write(1, " ", 1));
	else
		return (0);
}

int	ft_put_zero(t_form_spec *data, int nb_len, int sign_len)
{
	int	len;
	int	i;
	int	written;

	len = 0;
	if ((data->flag & FLAG_ZERO) && data->field_width > nb_len + sign_len)
		len = data->field_width - nb_len - sign_len;
	else if ((data->flag & FLAG_DOT) && data->precision > nb_len)
		len = data->precision - nb_len;
	i = 0;
	while (i < len)
	{
		written = write(1, "0", 1);
		if (written < 0)
			return (-1);
		i++;
	}
	return (len);
}
