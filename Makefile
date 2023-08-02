# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 13:46:33 by edecoste          #+#    #+#              #
#    Updated: 2023/08/02 16:56:21 by edecoste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

FLAGS = -Werror -Wall -Wextra -pthread -g3 -fsanitize=address

RM = rm -rf

SRCS = 	main.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_putendl_fd.c \
		ft_putstr_fd.c \
		utils.c \

OBJS 			= ${SRCS:%.c=./build/%.o}

HEADER			= include/philo.h

all: 			$(NAME)

${NAME}:		${OBJS}
					${CC} $^ ${FLAGS} -o ${NAME}

./build/%.o:	./src/%.c ${HEADER}
					@mkdir -p build
					${CC} ${FLAGS} -c $< -o $@

clean:
				${RM} -r ./build

fclean:			clean
				${RM} ${NAME}

re:				fclean
				${MAKE} all

FORCE:

.PHONY: all clean fclean re FORCE