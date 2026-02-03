# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 20:09:02 by sancuta           #+#    #+#              #
#    Updated: 2026/02/03 00:52:44 by sancuta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -MMD -MP -Wall -Wextra -Werror
LIBS = -Llibft -lft -lmlx -lXext -lX11
SRCS =	create_window.c \
		parser.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: .release $(NAME)

.release:
	if [ -f .debug ]; then $(MAKE) fclean; fi
	touch .release

$(NAME): $(OBJS)
	if [ -f .release ]; then $(MAKE) -C libft; \
	elif [ -f .debug ]; then $(MAKE) -C libft debug; \
	else $(MAKE) -C libft debug; fi
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME) .debug .release

re: fclean all

debug: CFLAGS += -g
debug: .debug $(NAME)

.debug:
	if [ -f .release ]; then $(MAKE) fclean; fi
	touch .debug

.PHONY: all clean fclean re debug

-include $(DEPS)
