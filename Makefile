# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamrire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 13:18:57 by yamrire           #+#    #+#              #
#    Updated: 2022/06/23 01:36:02 by yamrire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_nbr_base.c ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c ft_strlen.c ft_strnstr.c ft_substr.c ft_split.c ft_strjoin.c
NAME = pipex
BIBL = pipex.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:%.c=%.o)

all : $(NAME) 

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(BIBL) $(OBJ)
	$(CC) $(BIBL) main.c -o $(NAME)


clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
