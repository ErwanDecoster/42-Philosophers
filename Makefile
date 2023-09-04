# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 13:46:33 by edecoste          #+#    #+#              #
#    Updated: 2023/09/04 14:00:12 by edecoste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

FLAGS = -Werror -Wall -Wextra -pthread #-g3 -fsanitize=thread

RM = rm -rf

SRCS = 	actions.c \
		errors.c \
		exec.c \
		init.c \
		lib.c \
		main.c \
		utils.c

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