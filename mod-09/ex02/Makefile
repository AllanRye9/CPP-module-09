NAME =  PmergeMe

SRC = 	srcs/main.cpp srcs/RPN.cpp

HEADER_DIR = include

HEADER = -I $(HEADER_DIR)

OBJS = $(SRC:%.cpp=%.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 $(HEADER)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean: 
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

./PHONY: all re fclean clean