# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/17 19:44:26 by emadriga          #+#    #+#              #
#    Updated: 2021/09/04 19:19:09 by emadriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c		\
		operations1.c	\
		operations2.c	\
		order.c			\
		orderchunks.c	\
		orderchunks2.c	\
		parser.c		\
		parserutils.c	\
		longest_rally.c	\
		utils.c

NAME	= push_swap

CC 		= gcc
RM 		= rm -f

FLAGS	= -Wall -Wextra -Werror

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
