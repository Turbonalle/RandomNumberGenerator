NAME = RNG
CC = c++
FLAGS = -Wall -Wextra -Werror
SRC = RandomNumberGenerator.cpp
OBJ = $(SRC:.cpp=.o)
SRC_DIR = src
OBJ_DIR = obj

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/, $(OBJ))
	$(CC) $(FLAGS) $^ -o $@
	clear

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f numbers.txt

fclean: clean
	rm -f $(NAME)

re: fclean all