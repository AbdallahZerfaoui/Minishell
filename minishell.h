/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:14:52 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/06 20:12:32 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "minishell-lib/includes/libft.h"
# include "minishell-lib/includes/get_next_line.h"
# include "minishell-lib/includes/garbage_collector.h"
// # include "minishell_backup.h"
# include "pipex/pipex.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
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



// Lexer
t_token				*lexer(const char *line);

// Lexer utils
t_token				*create_token(char *value, t_token_type type);
t_token				*get_last_token(t_token *token);
void				append_token(t_token **head, t_token *new_token);
char				**lex_split(const char *str);
t_token				*array2linked_list(char **array);
void				free_all_split(char **split);

// Expander
t_token				*expand(t_token *tokens, char **env);
// void				print_tree(t_tree_node *root, int depth);
// void				print_tree(const t_tree_node *root, const char *prefix, bool is_last);
// void				print_tree_wrapper(const t_tree_node *root);
void				print_tree(t_tree_node *node, int depth, int is_last);
void				process_nodes(t_tree_node *root);
void				merge_tree_nodes(t_tree_node *root, char **expanded);
t_tree_node			*build_word_tree(char *word, char **env);

// Parser
t_cmd_node			*parse(t_token *tokens);

// Parser utils
t_cmd_node			*create_cmd_node(void);
void				append_cmd_node(t_cmd_node **head, t_cmd_node **new_node);
void				add_cmd(t_cmd_node **head, t_token *token);
void				add_file(t_cmd_node **head, t_token *token);
t_token				*move_forward_n(t_token *token, int n);
int					get_words_chain_len(t_token *token);
char				**linked_list2array(t_token *tokens);
int					len_cmds_lst(t_cmd_node *cmds);
t_cmd_node			*get_last_node(t_cmd_node *head);

// Parser errors
void				check_tokens(t_token *tokens);

// Utils
int					len_tokens_lst(t_token *tokens);
void				free_tokens(t_token *head);
void				free_cmds(t_cmd_node *head);
int					unbalanced_quotes(const char *str);

// t_exe	*parse_line(char *line, char **env);

#endif