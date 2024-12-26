
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
LIB_FLAGS = -lreadline
LIBS = libft.a
# EXECUTION_SRC = $(shell find ./src -name "*.c") $(wildcard ft_malloc/*.c)
# GNL_SRC = $(wildcard get_next_line/*.c)
# PIEPX_SRC = $(wildcard pipex/*.c)
# SRC = $(wildcard *.c) $(EXECUTION_SRC) $(PIEPX_SRC) $(GNL_SRC)
SRC = $(wildcard lexer/*.c)
OBJ = $(SRC:.c=.o)
NAME = minishell

#TEST : ls -la | grep "hello .txt" | sort > output.txt
#TEST : ls -la | grep ".txt" | sort | wc -l > output.txt

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

art:
	@echo "::::    ::::: ::::::::::: ::::    ::: ::::::::::: ::::::::  :::    ::: :::::::::: :::        :::        "
	@echo "+:+:+: :+:+:+     :+:     :+:+:   :+:     :+:    :+:    :+: :+:    :+: :+:        :+:        :+:        "
	@echo "+:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+    +:+        +:+    +:+ +:+        +:+        +:+        "
	@echo "+#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+    +#++:++#++ +#++:++#++ +#++:++#   +#+        +#+        "
	@echo "+#+       +#+     +#+     +#+  +#+#+#     +#+           +#+ +#+    +#+ +#+        +#+        +#+        "
	@echo "#+#       #+#     #+#     #+#   #+#+#     #+#    #+#    #+# #+#    #+# #+#        #+#        #+#        "
	@echo "###       ### ########### ###    #### ########### ########  ###    ### ########## ########## ########## "
	@echo "                                                               by The Greatest                          "

.PHONY: all clean fclean re art lib
