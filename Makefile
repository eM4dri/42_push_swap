# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/17 19:44:26 by emadriga          #+#    #+#              #
#    Updated: 2024/01/02 19:03:45 by emadriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program's name
NAME	= push_swap

CC 		= gcc
RM 		= rm -f

# compiling flags
FLAGS	=	-Wall -Wextra -Werror -Ofast $(SANITIZE)

# sanitize
# SANITIZE =
# SANITIZE = -fsanitize=address -g

# Header files
INCLUDES_FILES =	push_swap.h

# Source and object files
SRC_FILES		= main.c				\
				operations1.c			\
				operations2.c			\
				order.c					\
				parser.c				\
				parserutils.c			\
				get_longest_rally.c		\
				keep_longest_rally.c	\
				less_moves_to_order.c	\
				move_node_to_a.c		\
				calculate_node_moves.c	\
				utils.c

OBJ_FILES	= $(SRC_FILES:.c=.o)

# Folders
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES = $(addprefix $(INC_DIR), $(INCLUDES_FILES))

# all rule
all: obj $(NAME)

obj:
	mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INCLUDES)
	$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<
	
# Compiling
$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ)


clean:
		$(RM) -Rf $(OBJ_DIR)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.SILENT: all ${NAME} ${OBJS} clean fclean re

.PHONY:	all clean fclean re
