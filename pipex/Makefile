CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
NAME = pipex
NAME_BONUS = pipex_bonus

SRC = pipex.c find_path.c pipex_utils.c handle_children.c mandatory.c \
	ft_split.c ft_substr.c ft_strjoin.c ft_strncmp.c ft_strdup.c ft_strlen.c ft_calloc.c
SRC_BONUS = pipex.c find_path.c pipex_utils.c handle_children.c bonus.c \
	ft_split.c ft_substr.c ft_strjoin.c ft_strncmp.c ft_strdup.c ft_strlen.c ft_calloc.c
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
all: art $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) -g -o $(NAME_BONUS) $(OBJ_BONUS)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)
	$(RM) *.out *.exe

re: fclean all

valgrind: all bonus
	valgrind $(VFLAGS) ./$(NAME) infile "ls -l" "wc -l" outfile
	valgrind $(VFLAGS) ./$(NAME_BONUS) infile "cat" "sort -r" "wc -l" outfile

art:
	@echo " ____    ___   ____    _____  __  __"
	@echo "|  _ \  |_ _| |  _ \  | ____| \ \/ /"
	@echo "| |_) |  | |  | |_) | |  _|    \  / "
	@echo "|  __/   | |  |  __/  | |___   /  \ "
	@echo "|_|     |___| |_|     |_____| /_/\_\\"
	@echo "         by The Greatest         "

.PHONY: all clean fclean re bonus valgrind art