# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamrire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 13:18:57 by yamrire           #+#    #+#              #
#    Updated: 2022/06/21 01:55:43 by yamrire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_nbr_base.c ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c libft.h ft_strlen.c ft_strnstr.c ft_substr.c ft_split.c ft_strjoin.c
NAME = pipex.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:%.c=%.o)

all : $(NAME) 

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
