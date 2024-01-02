# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/17 19:44:26 by emadriga          #+#    #+#              #
#    Updated: 2024/01/02 16:49:55 by emadriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c		\
		operations1.c	\
		operations2.c	\
		order.c			\
		parser.c		\
		parserutils.c	\
		get_longest_rally.c	\
		keep_longest_rally.c	\
		less_moves_to_order.c	\
		move_node_to_a.c		\
		utils.c

NAME	= push_swap

CC 		= gcc
RM 		= rm -f

FLAGS	= -Wall -Wextra -Werror $(SANITIZE)

# sanitize
# SANITIZE =
SANITIZE = -fsanitize=address -g

OBJS	= $(SRC:.c=.o)

.c.o:
			$(CC) $(FLAGS) -c -o $@ $<

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.SILENT: all ${NAME} ${OBJS} clean fclean re

.PHONY:	all clean fclean re
