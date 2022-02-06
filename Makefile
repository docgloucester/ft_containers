# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/04 14:47:57 by rgilles           #+#    #+#              #
#    Updated: 2022/02/06 19:31:39 by rgilles          ###   ########.fr        #
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
FT_OBJS =	${SRCS:.cpp=.o_ft}
STD_OBJS =	${SRCS:.cpp=.o_std}

TSRCS =		ft_main.cpp
FT_TOBJS =	${TSRCS:.cpp=.o_ft}
STD_TOBJS =	${TSRCS:.cpp=.o_std}

RANDINT := ${shell bash -c 'echo $$RANDOM'}


%.o_ft:		%.cpp ${INCL} Makefile
	${CPPC} ${CPPFLAGS}          -c $< -o $@
%.o_std:	%.cpp ${INCL} Makefile
	${CPPC} ${CPPFLAGS} -DNS=std -c $< -o $@

all:		${NAME}

${NAME}:	${NAME}_ft

test:		${NAME}_test_ft

clean:
	rm -f ${FT_OBJS} ${STD_OBJS} ${FT_TOBJS} ${STD_TOBJS} .ft .std

fclean:		clean
	rm -f ${NAME}_ft ${NAME}_std ${NAME}_test_ft ${NAME}_test_std

re:			fclean ${NAME}

#private rules

${NAME}_ft:			${FT_OBJS} ${STD_OBJS}
	${CPPC} ${CPPFLAGS} -o ${NAME}_ft  ${FT_OBJS}
	${CPPC} ${CPPFLAGS} -o ${NAME}_std ${STD_OBJS}
	./${NAME}_ft  > .ft
	./${NAME}_std > .std
	diff .ft .std || :

${NAME}_test_ft:	${FT_TOBJS} ${STD_TOBJS}
	${CPPC} ${CPPFLAGS} -o ${NAME}_test_ft  ${FT_TOBJS}
	${CPPC} ${CPPFLAGS} -o ${NAME}_test_std ${STD_TOBJS}
	time nice ./${NAME}_test_std ${RANDINT}
	@echo "\n<------------------------------------------------------------------------------------------------------------------------------------>\n"
	time nice ./${NAME}_test_ft ${RANDINT}

.PHONY:		clean fclean re test