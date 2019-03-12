# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mshvets <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/17 15:49:35 by mshvets           #+#    #+#              #
#    Updated: 2018/12/17 15:50:18 by mshvets          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name of the executable file

NAME		:= fdf

# project directories

SRC_DIR     := ./
OBJ_DIR     := ./
INC_DIR     := ./incl/
LIB_DIR     := ./libft/

# project source files

SRC     	+= main.c
SRC     	+= validation.c
SRC     	+= drawing.c
SRC     	+= function.c
SRC     	+= function1.c

# project object files

OBJ		    = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# libraries

LIBFT       = $(LIBFT_DIR)libft.a
LIBFT_DIR   := $(LIB_DIR)
LIBFT_INC   := $(LIBFT_DIR)includes/
LIBFT_FLAGS := -lft -L $(LIBFT_DIR)

# compilation flags

CC_FLAGS	:= -Wall -Wextra -Werror

# linking flags

LINK_FLAGS  :=   $(LIBFT_FLAGS)

# header flags

HEADER_FLAGS  := -I $(INC_DIR) -I $(LIBFT_INC)

# compiler

CC 			:= gcc

HEAD 		= fdf.h

# rules

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
		@$(CC) $(OBJ) $(LINK_FLAGS) -o $(NAME) -lmlx -framework OpenGL -framework AppKit

$(OBJ_DIR)%.o: %.c
		@$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

$(LIBFT):
		make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

reclean: fclean all
	@rm -f $(OBJ)

