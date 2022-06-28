# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/15 12:57:07 by abigeddi          #+#    #+#              #
#    Updated: 2022/06/28 09:31:20 by abigeddi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

SRC =	ft_split.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strncmp.c \
		pipe.c \
		pipex.c \
		search_path.c \
		utils.c \

CC = cc

FLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $^

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
