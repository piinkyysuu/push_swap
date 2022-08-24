# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thle <thle@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 14:12:18 by thule             #+#    #+#              #
#    Updated: 2022/08/24 19:11:56 by thle             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
#FLAGS = -Wall -Wextra -Werror
CHECKER = checker
PUSH_SWAP = push_swap

INCLUDES_DIR = ./includes/

CHECKER_FILES = checker.c
PUSH_SWAP_FILES = push_swap_v2.c solve_small_stack.c solve_big_stack.c rotate_utils.c process_and_print_op.c
SHARED_FILES = operations.c stack_utils.c create_stack.c apply_op.c

CHECKER_SRC_DIR = ./srcs/checker/
CHECKER_SRC = $(addprefix $(CHECKER_SRC_DIR), $(CHECKER_FILES))

PUSH_SWAP_SRC_DIR = ./srcs/push_swap/
PUSH_SWAP_SRC = $(addprefix $(PUSH_SWAP_SRC_DIR), $(PUSH_SWAP_FILES))

SHARED_SRC_DIR = ./srcs/shared/
SHARED_SRC = $(addprefix $(SHARED_SRC_DIR), $(SHARED_FILES))

OBJS_DIR = ./objs/
CHECKER_OBJS = $(addprefix $(OBJS_DIR), $(CHECKER_FILES:%.c=%.o))
PUSH_SWAP_OBJS = $(addprefix $(OBJS_DIR), $(PUSH_SWAP_FILES:%.c=%.o))
SHARED_OBJS = $(addprefix $(OBJS_DIR), $(SHARED_FILES:%.c=%.o))

#this testing needs removing
TESTING_FILES = testing.c
TESTING_SRC = $(addprefix $(PUSH_SWAP_SRC_DIR), $(TESTING_FILES))
TESTING_OBJS = $(addprefix $(OBJS_DIR), $(TESTING_FILES:%.c=%.o))


LIB_DIR = ./libft/
LIB = $(addprefix $(LIB_DIR), libft.a)
LIB_INCLUDE = ./libft/includes/

# all: $(CHECKER)
all: $(PUSH_SWAP)

#this testing needs removing
testing: $(TESTING_OBJS) $(SHARED_OBJS) $(LIB)
	@$(CC) -o testing $(FLAGS) $(TESTING_OBJS) $(SHARED_OBJS) -L$(LIB_DIR) -lft

$(PUSH_SWAP): $(PUSH_SWAP_OBJS) $(SHARED_OBJS) $(LIB)
	@$(CC) -o $(PUSH_SWAP) $(FLAGS) $(PUSH_SWAP_OBJS) $(SHARED_OBJS) -L$(LIB_DIR) -lft

$(CHECKER): $(CHECKER_OBJS) $(SHARED_OBJS) $(LIB)
	@$(CC) -o $(CHECKER) $(FLAGS) $(CHECKER_OBJS) $(SHARED_OBJS) -L$(LIB_DIR) -lft

$(LIB): $(wildcard libft/*.o)
	@$(MAKE) -sC ./libft

$(OBJS_DIR)%.o: $(CHECKER_SRC_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@

$(OBJS_DIR)%.o: $(SHARED_SRC_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@

$(OBJS_DIR)%.o: $(PUSH_SWAP_SRC_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@

clean:
	@/bin/rm -rf $(OBJS_DIR)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@$(MAKE) -sC $(LIB_DIR) fclean
	@/bin/rm -f $(CHECKER) $(PUSH_SWAP)

re: fclean all
