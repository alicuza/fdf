/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:39:27 by sancuta           #+#    #+#             */
/*   Updated: 2026/01/25 15:46:25 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

//(1 << 0) // bits for '-': 00000001 =  1
# define FLAG_MINUS	1
//(1 << 1) // bits for '0': 00000010 =  2
# define FLAG_ZERO	2
//(1 << 2) // bits for '#': 00000100 =  4
# define FLAG_HASH	4
//(1 << 3) // bits for '+': 00001000 =  8
# define FLAG_PLUS	8
//(1 << 4) // bits for ' ': 00010000 = 16
# define FLAG_SPACE	16
//(1 << 5) // bits for '.': 00100000 = 32
# define FLAG_DOT	32
//(1 << 6) // bits for n<0: 01000000 = 64
# define FLAG_NEG	64
//(FLAG_NEG | FLAG_PLUS | FLAG_SPACE) // bits: 01011000 = 64 + 16 + 8 = 88
# define FLAG_SIGN	88

# define BASE_TEN "0123456789"
# define BASE_HEX_L "0123456789abcdef"
# define BASE_HEX_U "0123456789ABCDEF"

typedef struct s_format_specifier
{
	int					field_width;
	int					precision;
	unsigned int		flag;
	int					conv_spec;
}	t_form_spec;

extern const char	g_valid_conv_spec[];
extern const char	g_valid_flags[];
extern const int	g_allowed_flags[];

int			ft_printf(const char *s, ...);
t_form_spec	ft_get_form_spec(const char **s, const char *mask_set);
int			ft_prt_arg(t_form_spec *data, va_list *args);
int			ft_prt_int(t_form_spec *data, int n);
int			ft_prt_ptr(t_form_spec *data, unsigned long n);
int			ft_prt_hex(t_form_spec *data, unsigned long n, const char *base);
int			ft_prt_uint(t_form_spec *data, unsigned int n);
int			ft_put_space(t_form_spec *data, int nb_len, int sign_len);
int			ft_put_sign(t_form_spec *data);
int			ft_put_zero(t_form_spec *data, int nb_len, int sign_len);
int			ft_put_nbr_base(unsigned long n, const char *base);
int			ft_recurse(unsigned long n, const char *base,
				unsigned long base_len, int i);
int			ft_putchar(int c);
int			ft_get_nbr(const char **s);
int			ft_abs_nbr_len(unsigned long n, unsigned long base);
int			ft_form_spec_handler(t_form_spec *data, int flag, const char **s,
				va_list *args);
int			ft_check_form_spec(const char **s);
int			ft_check_written(int *written, int len);
#endif
