# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamrire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 13:18:57 by yamrire           #+#    #+#              #
#    Updated: 2022/11/07 07:58:56 by yamrire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_nbr_base.c ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c \
	ft_strlen.c ft_strnstr.c ft_substr.c ft_split.c ft_strjoin.c ft_strdup.c ft_strchr.c
SRC_P = process.c parsing_cmd.c main.c
SRC_B = main_bonus.c process_bonus.c parsing_cmd_bonus.c
NAME = pipex
BIBL = pipex.a
BIBL_B = pipex_bonus.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:%.c=%.o)
OBJ_P = $(SRC_P:%.c=%.o)
OBJ_B = $(SRC_B:%.c=%.o)

all : $(NAME) $(OBJ) $(OBJ_P)

$(NAME) : $(OBJ) $(OBJ_P)
	$(CC) $(CFLAGS) -c $(SRC) $(SRC_P)
	ar rc $(BIBL) $(OBJ) $(OBJ_P)
	$(CC) $(CFLAGS) $(BIBL) -o $(NAME)

clean : 
	rm -f $(OBJ)
	rm -f $(OBJ_P)
	rm -f $(BIBL)
	rm -f $(BIBL_B)
	rm -f $(OBJ_B)

fclean : clean
	rm -f $(NAME)
	
re : fclean all

bonus : $(BIBL_B)

$(BIBL_B) : $(OBJ) $(OBJ_B)
	$(CC) $(CFLAGS) -c $(SRC) $(SRC_B)
	ar rc $(BIBL_B) $(OBJ) $(OBJ_B)
	$(CC) $(CFLAGS) $(BIBL_B) -o $(NAME)