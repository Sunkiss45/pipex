# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 16:06:27 by ebarguil          #+#    #+#              #
#    Updated: 2021/12/20 17:02:29 by ebarguil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

LIB		=	-L ./Libft -lft

SRC		=	srcs/pipex.c \
			srcs/get_path.c \

OBJ		=	$(SRC:.c=.o)

CC		=	gcc

CF		=	-Wall -Wextra -Werror

CFS		=	-fsanitize=address -g3

RM		=	rm -rf

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			make -C Libft
			$(CC) $(CF) -o $(NAME) $(SRC) $(LIB)

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)
			make -C Libft fclean

re		:	fclean all

f		:	$(OBJ)
			make -C Libft
			$(CC) $(CF) $(CFS) -o $(NAME) $(SRC) $(LIB)

fre		:	fclean f

n		:
			norminette $(SRC)
			norminette include/pipex.h
			make -C Libft n

.PHONY	:	all clean fclean re f fre n nf
