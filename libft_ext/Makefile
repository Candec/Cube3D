# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/18 11:17:55 by jibanez-          #+#    #+#              #
#    Updated: 2023/03/21 19:05:42 by tpereira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	+= --quiet

SRC =  $(wildcard *.c)

OBJ = $(SRC:.c=.o)

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

so:
	$(CC) -fPIC -c $(CFLAGS) $(SRC)
	gcc -shared -o libft.so $(OBJ)

.PHONY: all clean fclean re
