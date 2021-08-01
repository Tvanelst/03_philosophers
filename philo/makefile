# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/30 16:56:01 by tvanelst          #+#    #+#              #
#    Updated: 2021/08/01 18:23:09 by tvanelst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -Iincludes

NAME		=	philo

SRCS		=	main.c utils.c

OBJ			=	${addprefix srcs/, ${SRCS:.c=.o}}


all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -g -fsanitize=address $(OBJ) $(LIBFT) -o $(NAME)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:			fclean all

.PHONY:		all fclean re
