/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 02:32:01 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/14 06:35:04 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prt_hex(t_form_spec *data, unsigned long n, const char *base)
{
	int	nb_len;
	int	sign_len;
	int	written[4];

	nb_len = ft_abs_nbr_len(n, 16);
	sign_len = 0;
	ft_memset(written, 0, sizeof(written));
	if (data->precision == -1)
		data->precision = 1;
	if (!n && !data->precision)
		nb_len = 0;
	if ((data->flag & FLAG_HASH) && n)
		sign_len += 2;
	if (!(data->flag & (FLAG_MINUS | FLAG_ZERO)))
		written[0] = ft_put_space(data, nb_len, sign_len);
	if ((data->flag & FLAG_HASH) && n)
		written[1] = ft_put_sign(data);
	if (data->flag & (FLAG_ZERO | FLAG_DOT))
		written[2] = ft_put_zero(data, nb_len, sign_len);
	if (nb_len)
		written[3] = ft_put_nbr_base(n, base);
	if (data->flag & FLAG_MINUS)
		written[0] = ft_put_space(data, nb_len, sign_len);
	return (ft_check_written(written, 4));
}

int	ft_prt_ptr(t_form_spec *data, unsigned long n)
{
	if (!n)
		return (write(1, "(nil)", 5));
	data->flag |= FLAG_HASH;
	return (ft_prt_hex(data, n, BASE_HEX_L));
}
