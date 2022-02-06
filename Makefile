# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/04 14:47:57 by rgilles           #+#    #+#              #
#    Updated: 2022/02/05 21:32:48 by rgilles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		ft_containers
CPPC =		clang++
CPPFLAGS =	-Wall -Wextra -Werror -std=c++98 -g3 -IMap -IVector -IStack

INCL =		common/equal.hpp common/lexicographical_compare.hpp common/enable_if.hpp \
			common/is_integral.hpp common/iterator_traits.hpp common/reverse_iterator.hpp\
			Stack/stack.hpp \
			Vector/vector.hpp Vector/vector_iterator.hpp \
			Map/map.hpp Map/tree_iterator.hpp Map/pair.hpp
SRCS =		main.cpp
OBJS =		${SRCS:.cpp=.o}
TSRCS =		ft_main.cpp
TOBJS =		${TSRCS:.cpp=.o}


%.o:		%.cpp ${INCL} Makefile
	${CPPC} ${CPPFLAGS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
	${CPPC} ${CPPFLAGS} -o ${NAME} ${OBJS}

test:		${TOBJS}
	${CPPC} ${CPPFLAGS} -o ${NAME}_test ${TOBJS}

clean:
	rm -f ${OBJS} ${TOBJS}

fclean:		clean
	rm -f ${NAME} ${NAME}_test

re:			fclean ${NAME}

.PHONY:		clean fclean re test