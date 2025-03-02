# -----------------------------------------------------------------------------
#  Makefile for Minishell
# -----------------------------------------------------------------------------

# =============================================================================
#  1.  COLOR DEFINITIONS
#      These variables define color codes for terminal output.
# =============================================================================
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

# =============================================================================
#  2.  TOOLCHAIN AND FLAGS
#      Defines the compiler, linker, and flags used for building.
# =============================================================================
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
LIB_FLAGS = -lreadline
LIBS = minishell-lib.a

# =============================================================================
#  3.  SOURCE FILES AND OBJECTS
#      Lists all source files and their corresponding object files.
# =============================================================================
BUILTINS_SRC := builtins_utils.c \
		cd_utils.c cd.c \
		echo_utils.c echo.c \
		env_utils.c print_env.c \
		exit_utils.c exit.c \
		export_utils.c export.c \
		unset.c pwd.c execute_builtins.c
BUILTINS_SRC := $(addprefix builtins/, $(BUILTINS_SRC))

EXECUTE_SRC := errors.c execute.c execute_utils.c \
		execute_utils2.c find_path.c handle_children.c \
		pipes.c handle_children_utils.c
EXECUTE_SRC := $(addprefix execute/, $(EXECUTE_SRC))

EXPANDER_SRC := build_word_tree_utils.c build_word_tree.c \
			expander.c handle_env_variables.c \
			handle_normal_word.c handle_variable_expansion.c \
			merge_tree_nodes.c process_nodes.c process_quotes.c \
			tree_node.c tree_utils.c
EXPANDER_SRC := $(addprefix expander/, $(EXPANDER_SRC))

HEREDOC_SRC := heredoc_loop.c heredoc_utils.c split_heredoc.c
HEREDOC_SRC := $(addprefix heredoc/, $(HEREDOC_SRC))

LEXER_SRC := lex_count_words.c lex_split.c lexer_utils.c \
			lexer.c token.c
LEXER_SRC := $(addprefix lexer/, $(LEXER_SRC))

PARSER_SRC := parser.c cmd_node_utils.c command_errors.c \
			token_errors.c token_processing.c \
			token_utils.c
PARSER_SRC := $(addprefix parser/, $(PARSER_SRC))

SIGNALS_SRC := signals.c setup_signals.c
SIGNALS_SRC := $(addprefix signals/, $(SIGNALS_SRC))

UTILS_SRC := utils.c cmds_lst_utils.c \
			memory.c standalone_redirections.c
UTILS_SRC := $(addprefix utils/, $(UTILS_SRC))

MAIN_SRC := main.c get_fds.c prepare_execution.c \
			read_and_validate_input.c shell_loop.c
MAIN_SRC := $(addprefix main/, $(MAIN_SRC))

SRC = $(UTILS_SRC) $(MAIN_SRC) $(LEXER_SRC) \
	$(EXPANDER_SRC) $(PARSER_SRC) $(EXECUTE_SRC) \
	$(BUILTINS_SRC) $(HEREDOC_SRC) $(SIGNALS_SRC)

OBJ = $(SRC:.c=.o)
NAME = minishell

# =============================================================================
#  4.  EXTERNAL RESOURCES
#      Information about external libraries or repositories.
# =============================================================================
GITHUB_REPO = https://github.com/AbdallahZerfaoui/minishell-lib
LIBS_DIR = minishell-lib

# =============================================================================
#  5.  TARGETS AND DEPENDENCIES
#      Defines the build process and dependencies between files.
# =============================================================================
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

# =============================================================================
#  6.  CLEANING AND MAINTENANCE
#      Rules for removing generated files.
# =============================================================================
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

# =============================================================================
#  7.  DEVELOPMENT AND TESTING
#      Targets for testing and debugging.
# =============================================================================
valgrind: re
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./$(NAME) 
# < tests/valgrind_test.txt
# valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./$(NAME) < valgrind_test.txt
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) < valgrind_test.txt

cppcheck: re
	cppcheck --enable=warning,style,performance,portability --enable=unusedFunction $(SRC)

# =============================================================================
#  8.  MESSAGES
#      Custom messages displayed during the build process.
# =============================================================================
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