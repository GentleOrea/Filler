#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 11:17:30 by ygarrot           #+#    #+#              #
#    Updated: 2018/01/18 11:22:07 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ygarrot.filler

SRC = parser.c resolve.c find_pos.c parser2.c init_and_erase.c 

INCLUDE =  includes/

FLAGS = -Wall -Werror -Wall

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@gcc -o $@ $(FLAGS) -c $<

$(LIBFT):
	@make -C libft

$(NAME): $(LIBFT) $(OBJ)
	 @gcc -o $(NAME) $^ -I $(INCLUDE) 

clean:
	@rm -f $(OBJ)
	@make -C libft clean
	
fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all, clean, fclean, re,
