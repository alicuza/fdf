/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:34:34 by sancuta           #+#    #+#             */
/*   Updated: 2025/12/14 06:20:44 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_prep_int(t_form_spec *data, int n, int *nb_len, int *sign_len);

int	ft_prt_int(t_form_spec *data, int n)
{
	int	nb_len;
	int	sign_len;
	int	written[4];

	ft_memset(written, 0, sizeof(written));
	ft_prep_int(data, n, &nb_len, &sign_len);
	if (!(data->flag & (FLAG_MINUS | FLAG_ZERO)))
		written[0] = ft_put_space(data, nb_len, sign_len);
	if (data->flag & FLAG_SIGN)
		written[1] = ft_put_sign(data);
	if (data->flag & (FLAG_ZERO | FLAG_DOT))
		written[2] = ft_put_zero(data, nb_len, sign_len);
	if (nb_len)
	{
		if (data->flag & FLAG_NEG)
			written[3] = ft_put_nbr_base((unsigned long)(-(long)n), BASE_TEN);
		else
			written[3] = ft_put_nbr_base((unsigned long)n, BASE_TEN);
	}
	if (data->flag & FLAG_MINUS)
		written[0] = ft_put_space(data, nb_len, sign_len);
	return (ft_check_written(written, 4));
}

static void	ft_prep_int(t_form_spec *data, int n, int *nb_len, int *sign_len)
{
	*sign_len = 0;
	*nb_len = ft_abs_nbr_len((unsigned long)n, 10);
	if (data->precision == -1)
		data->precision = 1;
	if (n < 0)
	{
		data->flag |= FLAG_NEG;
		*nb_len = ft_abs_nbr_len((unsigned long)(-(long)n), 10);
	}
	else if (!n && !data->precision)
		*nb_len = 0;
	if (data->flag & FLAG_SIGN)
		(*sign_len)++;
}

int	ft_check_written(int *written, int len)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (i < len)
	{
		if (written[i] == -1)
			return (-1);
		ret += written[i];
		i++;
	}
	return (ret);
}
