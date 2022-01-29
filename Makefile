# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/04 14:47:57 by rgilles           #+#    #+#              #
#    Updated: 2022/01/29 14:53:11 by rgilles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		ft_containers
CPPC =		c++
CPPFLAGS =	-Wall -Wextra -Werror -std=c++98 -g3 -IStack -IMap -IVector -Icommon

INCL =		Stack/stack.hpp Vector/vector.hpp Vector/VectorIterator.hpp utils/Equal.hpp utils/LexicographicalCompare.hpp
SRCS =		main.cpp
OBJS =		${SRCS:.cpp=.o}


%.o:		%.cpp ${INCL}
	${CPPC} ${CPPFLAGS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
	${CPPC} ${CPPFLAGS} -o ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean:		clean
	rm -f ${NAME}

re:			fclean ${NAME}

.PHONY:		clean fclean re