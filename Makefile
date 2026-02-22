# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 20:09:02 by sancuta           #+#    #+#              #
#    Updated: 2026/02/18 17:45:37 by sancuta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -MMD -MP -Wall -Wextra -Werror
LIBS = -lmlx -lXext -lX11 -lm
LIBFT = ./libft/libft.a
SRCS =	main.c \
		math_basic.c \
		math_constructors.c \
		math_vector_mult.c \
		math_quaternions.c \
		get_map_dimension.c \
		parsing.c \
		error_handling.c \
		transform_points.c \
		drawing.c \
		user_input.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: .release $(NAME)

.release:
	if [ -f .debug ]; then $(MAKE) fclean; fi
	touch .release

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(LIBFT): FORCE
	if [ -f .debug ]; then $(MAKE) -C libft debug; \
	else $(MAKE) -C libft; fi

FORCE:

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

.PHONY: all clean fclean re debug FORCE

-include $(DEPS)
