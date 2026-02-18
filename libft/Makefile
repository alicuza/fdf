# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 23:38:42 by sancuta           #+#    #+#              #
#    Updated: 2026/02/18 15:59:07 by sancuta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC ?= cc
CFLAGS ?= -MMD -MP -Wall -Wextra -Werror
ARFLAGS = -rcs
SRCS =	ft_isalpha.c \
		ft_issign.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_indchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstadd_back.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_get_form_spec.c \
		ft_printf_utils.c \
		ft_prt_hex.c \
		ft_prt_uint.c \
		ft_printf.c \
		ft_printf_padding.c \
		ft_print_handler.c \
		ft_prt_int.c \
		ft_put_nbr_base.c \
		get_next_line.c \
		get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: .release $(NAME)

.release:
	if [ -f .debug ]; then $(MAKE) fclean; fi
	touch .release

$(NAME): $(OBJS)
	ar $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME) .debug .release

re: fclean all

debug: CFLAGS += -g
debug: .debug $(NAME)

.debug:
	if [ -f .release ]; then $(MAKE) fclean; fi
	touch .debug

.PHONY: all clean fclean re debug

-include $(DEPS)
