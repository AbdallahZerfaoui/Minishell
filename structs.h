/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 21:40:44 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/04 20:31:33 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>

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
	TK_TILDE = '~',
	TK_BACK_SLASH = '\\',
	TK_NULL = '\0'
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
	int				need_expand;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_cmd_node
{
	int					index;
	t_token				*cmd;
	char				**cmd_array;
	t_token				*files;
	struct s_cmd_node	*next;
	struct s_cmd_node	*prev;
}					t_cmd_node;

typedef struct s_command
{
	char		*path;
	char		**args;
	int 		fd_in;
	int			fd_out; //magnific idea
}				t_command;

typedef struct s_cmd_manager
{
	int			nbr_cmds;
	int			**pipes;
	// int			fd_in;
	// int			fd_out;
	t_command	*cmds;
	t_cmd_node	*cmds_lst;
	pid_t		pid;
	char		**env;
}				t_cmd_manager;

typedef struct env_data
{
	char	**env;
	int		nbr_pipes;
}			t_env_data;

typedef struct s_tree_node
{
	char					*value;
	int						can_expand;
	struct s_tree_node		*parent;
	struct s_tree_node		*children;
	struct s_tree_node		*next_sibling;
}				t_tree_node;

typedef struct s_global_data {
    char **env;
    int exit_status;
    int nb_pipe;
} t_global_data;

t_global_data g_data;
#endif