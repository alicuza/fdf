# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 20:09:02 by sancuta           #+#    #+#              #
#    Updated: 2026/02/02 11:43:59 by sancuta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -MMD -MP -Wall -Wextra -Werror
LIBS = -lmlx -lXext -lX11 -Llibft -lft
SRCS =	create_window.c \
		parser.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	make -C libft clean
	rm -f $(OBJS) $(DEPS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: fclean all

.PHONY: all clean fclean re debug

-include $(DEPS)
