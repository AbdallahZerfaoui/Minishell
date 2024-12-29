# define standard colors
ifneq (,$(findstring xterm,${TERM}))
	BLACK        := $(shell tput -Txterm setaf 0)
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	WHITE        := $(shell tput -Txterm setaf 7)
	RESET := $(shell tput -Txterm sgr0)
else
	BLACK        := ""
	RED          := ""
	GREEN        := ""
	YELLOW       := ""
	LIGHTPURPLE  := ""
	PURPLE       := ""
	BLUE         := ""
	WHITE        := ""
	RESET        := ""
endif

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
LIB_FLAGS = -lreadline
LIBS = libft.a
# EXECUTION_SRC = $(shell find ./src -name "*.c") $(wildcard ft_malloc/*.c)
GNL_SRC = $(wildcard GetNextLine/*.c)
PIEPX_SRC = $(wildcard pipex/*.c)
LEXER_SRC = $(wildcard lexer/*.c)
PARSER_SRC = $(wildcard parser/*.c)
# SRC = $(EXECUTION_SRC) $(PIEPX_SRC) $(GNL_SRC)
SRC = $(LEXER_SRC) $(PARSER_SRC) $(wildcard *.c) $(PIEPX_SRC) $(GNL_SRC)
OBJ = $(SRC:.c=.o)
NAME = minishell

#TEST : ls -la | grep "hello .txt" | sort > output.txt
#TEST : ls -la | grep ".txt" | sort | wc -l > output.txt
#test : <"input file">"output file" | <cat>file

# $(info PIEPX_SRC = $(EXECUTION_SRC))
# $(info SRC = $(SRC))

# Rules
all: art lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_FLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@make fclean -C libft

lib:
	make -C libft

fclean: clean
	@$(RM) $(NAME)

re: fclean all

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) < valgrind_test.txt

cppcheck: re
	cppcheck --enable=warning,style,performance,portability --enable=unusedFunction $(SRC)


art:
	@echo "${GREEN}::::    ::::: ::::::::::: ::::    ::: ::::::::::: ::::::::  :::    ::: :::::::::: :::        :::        ${RESET}"
	@echo "${GREEN}+:+:+: :+:+:+     :+:     :+:+:   :+:     :+:    :+:    :+: :+:    :+: :+:        :+:        :+:        ${RESET}"
	@echo "+:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+    +:+        +:+    +:+ +:+        +:+        +:+        "
	@echo "+#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+    +#++:++#++ +#++:++#++ +#++:++#   +#+        +#+        "
	@echo "+#+       +#+     +#+     +#+  +#+#+#     +#+           +#+ +#+    +#+ +#+        +#+        +#+        "
	@echo "${RED}#+#       #+#     #+#     #+#   #+#+#     #+#    #+#    #+# #+#    #+# #+#        #+#        #+#        "
	@echo "${RED}###       ### ########### ###    #### ########### ########  ###    ### ########## ########## ########## ${RESET}"
	@echo "                                                               by The Greatest                          "

.PHONY: all clean fclean re art lib
