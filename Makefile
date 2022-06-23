# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thule <thule@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 14:12:18 by thule             #+#    #+#              #
#    Updated: 2022/06/23 15:28:37 by thule            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
#FLAGS = -Wall -Wextra -Werror
CHECKER = checker
PUSH_SWAP = push_swap

INCLUDES_DIR = ./includes/

CHECKER_FILES = checker.c
PUSH_SWAP_FILES = 

CHECKER_SRC_DIR = ./checker_srcs/
CHECKER_SRC = $(addprefix $(CHECKER_SRC_DIR), $(CHECKER_FILES))

PUSH_SWAP_SRC_DIR = ./push_swap_srcs/
PUSH_SWAP_SRC = $(addprefix $(PUSH_SWAP_SRC_DIR), $(PUSH_SWAP_FILES))

OBJS_DIR = ./objs/
CHECKER_OBJS = $(addprefix $(OBJS_DIR), $(CHECKER_FILES:%.c=%.o))
PUSH_SWAP_OBJS = $(addprefix $(OBJS_DIR), $(PUSH_SWAP_FILES:%.c=%.o))

LIB_DIR = ./libft/
LIB = $(addprefix $(LIB_DIR), libft.a)
LIB_INCLUDE = ./libft/includes/

all: $(CHECKER)

$(CHECKER): $(CHECKER_OBJS) $(LIB)
	@$(CC) -o $(CHECKER) $(FLAGS) $(CHECKER_OBJS) -L$(LIB_DIR) -lft

$(LIB): $(wildcard libft/*.o)
	@$(MAKE) -sC ./libft

$(OBJS_DIR)%.o: $(CHECKER_SRC_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@

clean:
	@/bin/rm -rf $(OBJS_DIR)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@$(MAKE) -sC $(LIB_DIR) fclean
	@/bin/rm -f $(CHECKER)

re: fclean all
