/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:14:52 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/26 22:41:43 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
// # include "minishell_backup.h"
// # include "pipex/pipex.h"
# include <errno.h>
# include <fcntl.h>
// # include <readline/history.h>
// # include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

enum				e_token
{
	TK_DOLLAR = '$',
	TK_S_QUOTE = '\'',
	TK_D_QUOTE = '"',
	TK_PIPE = '|',
	TK_QUESTION_MARK = '?',
	TK_SPACE = ' ',
	TK_NEW_LINE = '\n',
	TK_UNDERSCORE = '_',
	TK_HYPHEN = '-',
	TK_PERIOD = '.',
	TK_LESS = '<',
	TK_GREATER = '>',
};

typedef enum e_token_type //when use typedef and when only enum is enough
{
	WORD,
	PIPE,
	INFILE,
	OUTFILE
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_cmd_node
{
	t_token				*cmd;
	t_token				*files;
	struct s_cmd_node	*next;
	struct s_cmd_node	*prev;
}					t_cmd_node;

// Lexer
t_token				*lexer(const char *line);

// Lexer utils
t_token				*create_token(char *value, t_token_type type);
t_token				*get_last_token(t_token *token);
void				append_token(t_token **head, t_token *new_token);
char				**lex_split(const char *str);
t_token				*array2linked_list(char **array);

// Parser
t_cmd_node			*parse(t_token *tokens);

// Parser utils
t_cmd_node			*create_cmd_node(void);
void				append_cmd_node(t_cmd_node **head, t_cmd_node *new_node);
void				add_cmd(t_cmd_node **head, t_token *token);
void				add_file(t_cmd_node **head, t_token *token);

// Utils
int					len_tokens_lst(t_token *tokens);

// t_exe	*parse_line(char *line, char **env);

#endif