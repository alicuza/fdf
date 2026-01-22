/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 01:53:58 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/14 06:21:11 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_prep_uint(t_form_spec *data, unsigned int n, int *nb_len);

int	ft_prt_uint(t_form_spec *data, unsigned int n)
{
	int	nb_len;
	int	written[3];

	ft_memset(written, 0, sizeof(written));
	ft_prep_uint(data, n, &nb_len);
	if (!(data->flag & (FLAG_MINUS | FLAG_ZERO)))
		written[0] = ft_put_space(data, nb_len, 0);
	if (data->flag & (FLAG_ZERO | FLAG_DOT))
		written[1] = ft_put_zero(data, nb_len, 0);
	if (nb_len)
		written[2] = ft_put_nbr_base(n, "0123456789");
	if (data->flag & FLAG_MINUS)
		written[0] = ft_put_space(data, nb_len, 0);
	return (ft_check_written(written, 3));
}

static void	ft_prep_uint(t_form_spec *data, unsigned int n, int *nb_len)
{
	*nb_len = ft_abs_nbr_len((unsigned long)n, 10);
	if (data->precision == -1)
		data->precision = 1;
	if (!n && !data->precision)
		*nb_len = 0;
}
