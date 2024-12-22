
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
LIB_FLAGS = -lreadline
LIBS = libft.a
EXECUTION_SRC = $(wildcard execution_backup/*.c) $(wildcard execution_backup/buildins/*.c)
SRC = main.c $(EXECUTION_SRC)
OBJ = $(SRC:.c=.o)
NAME = minishell

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

.PHONY: all clean fclean re art
