# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/04 14:47:57 by rgilles           #+#    #+#              #
#    Updated: 2022/02/05 14:55:05 by rgilles          ###   ########.fr        #
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


%.o:		%.cpp ${INCL} Makefile
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