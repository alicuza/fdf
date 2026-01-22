/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:55:17 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/14 15:33:09 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	g_valid_flags[] = "-0#+ ";

const char	g_valid_conv_spec[] = "csdiupxX";

const int	g_allowed_flags[] = {
	FLAG_MINUS,
	FLAG_MINUS | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_PLUS | FLAG_SPACE | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_DOT,
	FLAG_MINUS,
	FLAG_MINUS | FLAG_ZERO | FLAG_HASH | FLAG_DOT,
	FLAG_MINUS | FLAG_ZERO | FLAG_HASH | FLAG_DOT
};

static int	ft_prt_char(t_form_spec *data, int c);
static int	ft_prt_str(t_form_spec *data, char *s);

int	ft_printf(const char *s, ...)
{
	size_t		res;
	int			written;
	va_list		args;
	int			flag;
	t_form_spec	data;

	if (!s)
		return (-1);
	va_start(args, s);
	res = 0;
	ft_memset(&data, 0, sizeof(data));
	while (*s)
	{
		flag = ft_check_form_spec(&s);
		written = ft_form_spec_handler(&data, flag, &s, &args);
		if (written < 0)
		{
			va_end(args);
			return (-1);
		}
		res += written;
	}
	va_end(args);
	return (res);
}

int	ft_prt_arg(t_form_spec *data, va_list *args)
{
	int	written;

	written = 0;
	if (data->conv_spec == 'c')
		written = ft_prt_char(data, va_arg(*args, int));
	else if (data->conv_spec == 's')
		written = ft_prt_str(data, va_arg(*args, char *));
	else if (data->conv_spec == 'p')
		written = ft_prt_ptr(data, (unsigned long)va_arg(*args, void *));
	else if (data->conv_spec == 'd' || data->conv_spec == 'i')
		written = ft_prt_int(data, va_arg(*args, int));
	else if (data->conv_spec == 'u')
		written = ft_prt_uint(data, va_arg(*args, unsigned int));
	else if (data->conv_spec == 'x')
		written = ft_prt_hex(data, va_arg(*args, unsigned int), BASE_HEX_L);
	else if (data->conv_spec == 'X')
		written = ft_prt_hex(data, va_arg(*args, unsigned int), BASE_HEX_U);
	return (written);
}

static int	ft_prt_char(t_form_spec *data, int c)
{
	int	written[2];

	ft_memset(written, 0, sizeof(written));
	if (!(data->flag & FLAG_MINUS))
		written[0] = ft_put_space(data, 1, 0);
	written[1] = write(1, &c, 1);
	if (data->flag & FLAG_MINUS)
		written[0] = ft_put_space(data, 1, 0);
	return (ft_check_written(written, 2));
}

/*
	How would a buffer work here? I could fill it from the back
	with spaces, then zeros and the sign, then the digits.
	Problem: there is no way to know what size it should be beforehand.
	So either I have a standard big buffer (maybe on the stack),
	or I malloc and realloc to the necessary size to write every
	successive element into the buffer, if it is too small.
 */

static int	ft_prt_str(t_form_spec *data, char *s)
{
	int	len;
	int	written[2];

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	ft_memset(written, 0, sizeof(written));
	if ((data->flag & FLAG_DOT) && (data->precision != -1)
		&& (len > data->precision))
		len = data->precision;
	ft_memset(written, 0, sizeof(written));
	if (!(data->flag & FLAG_MINUS))
		written[0] = ft_put_space(data, len, 0);
	written[1] = write(1, s, len);
	if (data->flag & FLAG_MINUS)
		written[0] = ft_put_space(data, len, 0);
	return (ft_check_written(written, 2));
}
