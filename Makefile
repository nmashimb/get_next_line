# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmashimb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/29 12:17:06 by nmashimb          #+#    #+#              #
#    Updated: 2019/07/03 17:43:52 by nmashimb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
SRC = get_next_line.c
FLAGS = -Wall -Wextra -Werror
OBJ = get_next_line.o

all: $(NAME)
&(NAME): 
		gcc $(FLAGS) -c $(SRC)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)
clean:
		rm -f (OBJ)
fclean: clean
		rm -f $(NAME)
re: fclean all
