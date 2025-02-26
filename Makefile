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
LIBS = minishell-lib.a
GITHUB_REPO = https://github.com/AbdallahZerfaoui/minishell-lib
LIBS_DIR = minishell-lib

BUILTINS_SRC = $(wildcard builtins/*.c)
EXECUTE_SRC = $(wildcard execute/*.c)
EXPANDER_SRC = $(wildcard expander/*.c)
HEREDOC_SRC = $(wildcard heredoc/*.c)
LEXER_SRC = $(wildcard lexer/*.c)
MAIN_SRC = $(wildcard main/*.c)
PARSER_SRC = $(wildcard parser/*.c)
SIGNALS_SRC = $(wildcard signals/*.c)
UTILS_SRC = $(wildcard utils/*.c)
SRC = $(UTILS_SRC) $(MAIN_SRC) $(LEXER_SRC) $(EXPANDER_SRC) $(PARSER_SRC) $(EXECUTE_SRC) $(BUILTINS_SRC) $(HEREDOC_SRC) $(SIGNALS_SRC)

OBJ = $(SRC:.c=.o)
NAME = minishell

# Rules
all: setup build

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_FLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

download_resources:
	git submodule update --init --remote --recursive 
#be careful with this command it doesnt update if you delete the folder
setup: art download_resources libs

build: $(NAME) success_message

libs:
	make -C $(LIBS_DIR)
	@echo "${GREEN}Librarie $(LIBS) compiled successfully!${RESET}"

collect_tester_garbage:
	@$(RM) echo 
	@$(RM) "out|cd"
	@$(RM) tmp*
	@$(RM) lol*

clean:
	@$(RM) $(OBJ)

fclean: clean collect_tester_garbage
	@$(RM) $(NAME) *.a
	@if [ -d "$(LIBS_DIR)" ]; then \
		$(MAKE) fclean -C $(LIBS_DIR); \
	fi

re: fclean all

valgrind: re
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./$(NAME) 
# < tests/valgrind_test.txt
# valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./$(NAME) < valgrind_test.txt
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) < valgrind_test.txt

cppcheck: re
	cppcheck --enable=warning,style,performance,portability --enable=unusedFunction $(SRC)

success_message:
	@echo "\033[31m	------------------***༺ (\033[31m\033[32mMinishell Compiled!\033[31m)༻***------------------\n\033[0m"

art:
	@echo "${GREEN}::::    ::::: ::::::::::: ::::    ::: ::::::::::: ::::::::  :::    ::: :::::::::: :::        :::        ${RESET}"
	@echo "${GREEN}+:+:+: :+:+:+     :+:     :+:+:   :+:     :+:    :+:    :+: :+:    :+: :+:        :+:        :+:        ${RESET}"
	@echo "+:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+    +:+        +:+    +:+ +:+        +:+        +:+        "
	@echo "+#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+    +#++:++#++ +#++:++#++ +#++:++#   +#+        +#+        "
	@echo "+#+       +#+     +#+     +#+  +#+#+#     +#+           +#+ +#+    +#+ +#+        +#+        +#+        "
	@echo "${RED}#+#       #+#     #+#     #+#   #+#+#     #+#    #+#    #+# #+#    #+# #+#        #+#        #+#        "
	@echo "${RED}###       ### ########### ###    #### ########### ########  ###    ### ########## ########## ########## ${RESET}"
	@echo "                                                               by The Greatest                          "

.PHONY: all clean fclean re art valgrind cppcheck collect_tester_garbage success_message setup build libs