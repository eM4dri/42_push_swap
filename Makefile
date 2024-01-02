# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/17 19:44:26 by emadriga          #+#    #+#              #
#    Updated: 2024/01/02 20:40:12 by emadriga         ###   ########.fr        #
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

# ALL
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
LIBFT_DIR = ./libft/

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES = $(addprefix $(INC_DIR), $(INCLUDES_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# Libft linkers
LNK  = -L $(LIBFT_DIR) -lft $(SANITIZE)

# all rule
all: obj $(LIBFT) $(NAME)

obj:
	mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INCLUDES)
	$(CC) $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
	
$(LIBFT):
	@make -C $(LIBFT_DIR)
	
# Compiling
$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(LNK) -o $(NAME) $(OBJ)

# BONUS
# Program's name
NAME_B	= checker

# Header files
INCLUDES_FILES_B =	push_swap.h

# Source and object files
SRC_FILES_B		= main.c				\
				operations.c			\
				parser.c				\
				parserutils.c

OBJ_FILES_B	= $(SRC_FILES_B:.c=.o)

# Folders
SRC_DIR_B = ./src_b/
OBJ_DIR_B = ./obj_b/
INC_DIR_B = ./inc_b/

# Paths
SRC_B = $(addprefix $(SRC_DIR_B), $(SRC_FILES_B))
OBJ_B = $(addprefix $(OBJ_DIR_B), $(OBJ_FILES_B))
INCLUDES_B = $(addprefix $(INC_DIR_B), $(INCLUDES_FILES_B))

# bonus rule
bonus: obj_b $(LIBFT) $(NAME_B)

obj_b:
	mkdir -p $(OBJ_DIR_B)
$(OBJ_DIR_B)%.o:$(SRC_DIR_B)%.c $(INCLUDES_B)
	$(CC) $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR_B) -o $@ -c $<
	
# Compiling
$(NAME_B):	$(OBJ_B)
			$(CC) $(FLAGS) $(LNK) -o $(NAME_B) $(OBJ_B)

clean:
		$(RM) -Rf $(OBJ_DIR)
		$(RM) -Rf $(OBJ_DIR_B)
		make -C $(LIBFT_DIR) clean

fclean:	clean
		$(RM) $(NAME)
		$(RM) $(NAME_B)
		make -C $(LIBFT_DIR) fclean

re:		fclean all

.SILENT: all ${NAME} ${OBJ} clean fclean re bonus ${LIBFT} ${NAME_B} ${OBJ_B}

.PHONY:	all clean fclean re bonus
