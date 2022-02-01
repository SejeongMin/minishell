# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 12:49:29 by soum              #+#    #+#              #
#    Updated: 2022/02/01 17:30:34 by soum             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = main.c \
	   src/init_shell.c \
	   src/prompt.c \
	   src/check_cmd.c \
	   src/parsing_cmd.c \
	   src/error.c \
	   src/free_list.c \

LIBFT = libft
LIBFT_LIB = Libft/libft.a
INCLUDES = ./includes/minishell.h

CC = gcc
CFLAGES = -Wall -Wextra -Werror
COMFILE_FLAGS = -lreadline -L /opt/homebrew/opt/readline/lib
OBJ_FLAGS = -I /opt/homebrew/opt/readline/include

.c.o :
	$(CC) $(CFLAGES) $(OBJ_FLAGS) -c $< -o $(<:.c=.o) -I $(INCLUDES)

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	$(CC) $(CFLAGES) $(OBJS) $(COMFILE_FLAGS) $(LIBFT_LIB) -o $(NAME)

re : fclean all

clean :
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean : clean
	rm -f $(NAME)
	rm -f $(LIBFT_LIB)
