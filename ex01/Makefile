NAME	= RPN

SRCS = RPN.cpp \
main.cpp \
utils.cpp \

HEADER = RPN.hpp

OBJS	=	${SRCS:.cpp=.o}

CXX			= 	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g
RM			= 	rm -f

.cpp.o	:
			${CXX} ${CXXFLAGS} -c $< -o ${<:.cpp=.o}

all		:	${NAME}

${NAME}	:	${OBJS} ${HEADER}
			${CXX} ${CXXFLAGS} -o ${NAME} ${OBJS}

clean	:	
			${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY : all clean fclean re
