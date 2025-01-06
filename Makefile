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
FOLDER_NAME = minishell-lib
LIBS_DIR = minishell-lib
ZIP_URL = $(GITHUB_REPO)/archive/main.zip
# EXECUTION_SRC = $(shell find ./src -name "*.c") $(wildcard ft_malloc/*.c)
# GNL_SRC = $(wildcard GetNextLine/*.c)
PIEPX_SRC = $(wildcard pipex/*.c)
LEXER_SRC = $(wildcard lexer/*.c)
PARSER_SRC = $(wildcard parser/*.c)
EXPANDER_SRC = $(wildcard expander/*.c)
COLLECTOR_SRC = $(wildcard $(LIBS_DIR)/collector/*.c)
# SRC = $(EXECUTION_SRC) $(PIEPX_SRC) $(GNL_SRC)
# SRC = $(LEXER_SRC) $(PARSER_SRC) $(wildcard *.c) $(PIEPX_SRC) $(GNL_SRC) $(EXPANDER_SRC)
SRC = $(wildcard *.c) $(LEXER_SRC) $(EXPANDER_SRC) $(PARSER_SRC) $(PIEPX_SRC) $(COLLECTOR_SRC)

OBJ = $(SRC:.c=.o)
NAME = minishell

#TEST : ls -la | grep "hello .txt" | sort > output.txt
#TEST : ls -la | grep ".txt" | sort | wc -l > output.txt
#test : <"input file">"output file" | <cat>file

# $(info PIEPX_SRC = $(EXECUTION_SRC))
# $(info SRC = $(SRC))

# Rules
all: setup build

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_FLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



download_resources:
	@if [ ! -d "./$(FOLDER_NAME)" ]; then \
		echo "${GREEN}Downloading $(FOLDER_NAME) from GitHub...${RESET}"; \
		mkdir -p $(LIBS_DIR); \
		curl -L $(ZIP_URL) -o $(LIBS_DIR)/repo.zip; \
		unzip $(LIBS_DIR)/repo.zip -d $(LIBS_DIR); \
		mv $(LIBS_DIR)/minishell-lib-main/* $(LIBS_DIR)/; \
		rm -rf $(LIBS_DIR)/minishell-lib-main $(LIBS_DIR)/repo.zip; \
		echo "${GREEN}$(FOLDER_NAME) downloaded successfully!${RESET}"; \
	else \
		echo "${GREEN}$(FOLDER_NAME) already exists. Skipping download.${RESET}"; \
	fi

setup: art download_resources libs

build: $(NAME) success_message

libs:
	make re -C $(LIBS_DIR)
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

	
re: fclean setup build


valgrind: re
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./$(NAME) < valgrind_test.txt
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) < valgrind_test.txt
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

.PHONY: all clean fclean re art lib valgrind cppcheck collect_tester_garbage success_message