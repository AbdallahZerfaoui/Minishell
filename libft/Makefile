# Name of the library
NAME = ../libft.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# List of source files
SRC = $(wildcard *.c)

# Object files (by replacing .c with .o)
OBJ = $(SRC:.c=.o)

# Default target
all: $(NAME)

# Rule to create the library
$(NAME): $(OBJ)
	@$(AR) rcs $(NAME) $(OBJ)
	@echo "Library $(NAME) created."

# Rule to compile .c files into .o files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< into $@."

# Clean the object files
clean:
	@rm -f $(OBJ)
	@echo "Object files cleaned."

# Clean everything including the library
fclean: clean
	@rm -f $(NAME)
	@echo "Library $(NAME) removed."

# Recompile everything
re: fclean all


.PHONY: all clean fclean re