##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC			=	src/yams.cpp

SRC_MAIN	=	src/main.cpp

NAME		=	201yams

OBJ			=	$(SRC:%.cpp=%.o)

OBJ_MAIN	=	$(SRC_MAIN:%.cpp=%.o)

CXXFLAGS	=	-Wall -Wextra

CXX			=	g++

all:		$(NAME)

$(NAME):	$(OBJ_MAIN) $(OBJ)
		$(CXX) $(SRC_MAIN) $(SRC) -o $(NAME) $(LDFLAGS)

clean:
		rm -f $(OBJ) $(OBJ_MAIN)

fclean:		clean
		rm -f $(NAME)
		rm -f $(TEST_NAME)
		rm -f *.gcno
		rm -f *.gcda

re:		fclean all
