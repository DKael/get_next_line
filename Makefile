# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 20:28:31 by hyungdki          #+#    #+#              #
#    Updated: 2023/09/24 23:18:19 by hyungdki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS =	get_next_line.c	\
		    get_next_line_utils.c \

OBJS = 	${SRCS:.c=.o}

SRCS_BONUS =	get_next_line_bonus.c	\
		          get_next_line_utils_bonus.c \

OBJS_BONUS = 	${SRCS_BONUS:.c=.o}

NAME = libgnl.a

ifdef WITH_BONUS
	TOTAL_OBJS = ${OBJS_BONUS}
else
	TOTAL_OBJS = ${OBJS}
endif

${NAME} : ${TOTAL_OBJS}
		@ar -rsc ${NAME} ${TOTAL_OBJS}

%.o :%.c
	@${CC} ${CFLAGS} -c -I. $< -o $@

all : ${NAME}

clean:
	rm -f $(OBJS)

fclean: 
	@$(MAKE) clean
	rm -f  ${NAME}

re: 
	@$(MAKE) fclean
	@$(MAKE) all

bonus:
	@make WITH_BONUS=1

.PHONY: all clean fclean re
