# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zmaziane <zmaziane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 23:14:34 by zmaziane          #+#    #+#              #
#    Updated: 2022/06/27 21:21:51 by zmaziane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
#FLAGS = -Wall -Wextra -Werror

# -I
RL_INCLUDE = $(addprefix $(shell brew --prefix readline), /include)
# -L
RL_LIB = $(addprefix $(shell brew --prefix readline), /lib)
LIB = minishell.h

SRCS = mini.c liste.c parsing/token00.c parsing/token01.c parsing/token02.c syntax/syntax.c

OBJ = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -L $(RL_LIB) -lreadline -o $(NAME)

%.o:%.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@ -I $(RL_INCLUDE)
	

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
