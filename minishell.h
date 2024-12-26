/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:14:52 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/26 16:00:15 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
// # include "minishell_backup.h"
// # include "pipex/pipex.h"
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <termios.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

enum	e_token
{
	TK_DOLLAR = '$',
	TK_S_QUOTE = '\'',
	TK_D_QUOTE = '"',
	TK_LESS = '<',
	TK_GREATER = '>',
	TK_PIPE = '|',
	TK_QUESTION_MARK = '?',
	TK_SPACE = ' ',
	TK_NEW_LINE = '\n',
	TK_UNDERSCORE = '_',
	TK_HYPHEN = '-',
	TK_PERIOD = '.',
};

typedef struct s_token
{
	char			*value;
	char			*type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Lexer


// t_exe	*parse_line(char *line, char **env);

#endif