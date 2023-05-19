NAME	= btc	

SRCS = BitcoinExchange.cpp \
main.cpp \

HEADER = BitcoinExchange.hpp

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

run   : ${NAME}
			"./${NAME} input.txt"

.PHONY : all clean fclean re run
