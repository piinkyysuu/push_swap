# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thule <thule@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 12:18:03 by thule             #+#    #+#              #
#    Updated: 2022/06/23 14:11:24 by thule            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libft.a

FILES = ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlen.c ft_strncpy.c ft_strncmp.c ft_strcat.c ft_strncat.c ft_strstr.c ft_strnstr.c ft_memset.c ft_bzero.c ft_memcpy.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr_fd.c ft_putnbr.c ft_strlcat.c ft_memccpy.c ft_memmove.c ft_strchr.c ft_strrchr.c ft_memchr.c ft_memcmp.c ft_atoi.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strsplit.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_lstaddlast.c ft_isspace.c get_next_line.c ft_lltoa.c ft_ulltoa.c ft_max.c ft_min.c ft_abs.c

SRCS_DIR = ./srcs/
SRCS = $(addprefix $(SRCS_DIR), $(FILES))

OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(FILES:%.c=%.o))

INCLUDES_DIR = ./includes/

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $@ $^
	@ranlib $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -c $^ -o $@

clean:
	@/bin/rm -rf $(OBJS_DIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
