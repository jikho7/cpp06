NAME = convert
SRC = main.cpp ScalarConverter.cpp
OBJ := $(SRC:%.cpp=%.o)
CXXFLAGS = -Wall -Werror -Wextra -Wno-conversion -std=c++98 -fsanitize=address -g
CXX = g++

all : $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 


