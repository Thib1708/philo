# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 15:42:44 by tgiraudo          #+#    #+#              #
#    Updated: 2023/05/23 17:04:40 by thibaultgir      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PRINT	= @printf

# SOURCES
LIST_SRCS	 = main.c	\
				ft_check.c \
				ft_check_philo.c	\
				ft_philo.c \
				ft_exit.c	\
				utils.c	\

OBJS = $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))
SRCS  = ${addprefix ${DIR_SRCS}, ${LIST_SRCS}}

# DIRECTORIES
DIR_SRCS = srcs/
DIR_OBJS = .objs/
DIR_INCLUDE = include/
D_UTILS = utils/

# VARIABLES
NAME	= philo
CC			  = cc
CFLAGS  = -Wall -Wextra -Werror
RM			  = rm -rf
MAKEFLAGS += --no-print-directory

# COLORS
RED			 = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE	= \033[1;34m
CYAN	= \033[1;36m
DEFAULT = \033[0m
SUPPR   = \r\033[2K

# COMPILATION
all :		  ascii ${NAME}

${DIR_OBJS}%.o: %.c	 ${DIR_INCLUDE}philo.h Makefile
						@mkdir -p $(shell dirname $@)
						@${PRINT} "${YELLOW}${SUPPR}Creating ${NAME}'s objects : $@"
						@${CC} ${CFLAGS} -I ${DIR_INCLUDE} -c $< -o $@ 

${NAME}:		${OBJS}
						@${PRINT} "${GREEN}${SUPPR}Creating ${NAME}'s objects : DONE\n"
						@${PRINT} "${YELLOW}Compiling ${NAME}...${DEFAULT}"
						@${CC} ${OBJS} -fsanitize=thread -o ${NAME} -pthread
						@${PRINT} "${GREEN}${SUPPR}Compiling ${NAME} : DONE ${DEFAULT}\n\n"

ascii :
						@${PRINT} "$$ASCII"

clean :		 ascii
						@${PRINT} "${RED}Deleting objects : DONE\n"
						@${RM} ${DIR_OBJS}

fclean :		clean 
						@${PRINT} "${RED}Deleting executable : DONE${DEFAULT}\n\n"
						@${RM} ${NAME} 

re :			fclean all

define ASCII
${CYAN}
██████╗ ██╗  ██╗██╗██╗      ██████╗     
██╔══██╗██║  ██║██║██║     ██╔═══██╗    
██████╔╝███████║██║██║     ██║   ██║    
██╔═══╝ ██╔══██║██║██║     ██║   ██║    
██║     ██║  ██║██║███████╗╚██████╔╝    
╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝  
${DEFAULT}

endef
export ASCII

.PHONY : all re clean fclean lib ascii