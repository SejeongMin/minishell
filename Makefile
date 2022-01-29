# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 12:49:29 by soum              #+#    #+#              #
#    Updated: 2022/01/11 12:53:05 by soum             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = main.c \

LIBFT = libft
LIBFT_LIB = Libft/libft.a
INCLUDES = ./includes/minishell.h

CC = gcc
CFLAGES = -Wall -Wextra -Werror

.c.o :
	$(CC) $(CFLAGES) -c $< -o $(<:.c=.o) -I $(INCLUDES)

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	$(CC) $(CFLAGES) $(OBJS) $(LIBFT_LIB) -o $(NAME)

re : fclean all

clean :
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean : clean
	rm -f $(NAME)
	rm -f $(LIBFT_LIB)
