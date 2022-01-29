# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 12:49:29 by soum              #+#    #+#              #
#    Updated: 2022/01/29 15:05:22 by semin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = main.c \

LIBFT = libft
LIBFT_LIB = Libft/libft.a
INCLUDES = ./includes/minishell.h

CC = gcc
CFLAGES = -Wall -Wextra -Werror
READLINEFLAGS = -lreadline $(READLINELIBDIR)

COMFILE_FLAGS = -lreadline -L ~/.brew/opt/readline/lib
OBJ_FLAGS = -I ~/.brew/opt/readline/include
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
