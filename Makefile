# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 11:12:25 by tgiraudo          #+#    #+#              #
#    Updated: 2022/12/15 13:32:09 by tgiraudo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

FLAGS		= -Wall -Wextra -Werror

CC 			= gcc

HEADER_PATH	= include/

HEADER		= ${HEADER_PATH}philo.h

INCLUDES 	= -I ${HEADER_PATH}

THREAD		= -lpthread -DLinux

SRCS		=	srcs/main.c			\
				srcs/utils.c		\
				srcs/ft_philo.c		\
				srcs/ft_atoi.c
				
OBJS		= ${SRCS:.c=.o}

%.o 		: %.c ${HEADER} Makefile
				@${CC} ${FLAGS} ${INCLUDES} -c $< -o $@ 

${NAME}		: ${OBJS}
				@${CC} -fsanitize=address ${OBJS} -o ${NAME}
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

all			: ${NAME}

clean		:
				@rm -f ${OBJS}
				@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean		: clean
				@rm -f ${NAME}
				@echo "$(RED)${NAME} deleted!$(DEFAULT)"

re			: fclean all

.PHONY		: all clean fclean re

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
