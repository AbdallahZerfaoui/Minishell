/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:14:52 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 16:41:20 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell-lib/includes/garbage_collector.h"
# include "minishell-lib/includes/get_next_line.h"
# include "minishell-lib/includes/libft.h"
# include "signals/signals.h" //TODO replace it
# include "structs.h"         // this line must be called before pipex
# include "execute/pipex.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

# define HEREDOC_FILE "_heredoc.txt"

// Main
void			shell_loop(t_shell **shell);
char			*read_and_validate_input(int is_interactive);
t_cmd_manager	*prepare_execution(t_cmd_node *cmds, t_shell **shell);
int				get_fd_in(t_cmd_node *node);
int				get_fd_out(t_cmd_node *node);
t_heredoc		*init_heredoc_struct(char *stop_word, char *hd_filename,
					t_shell **shell);

// Lexer
t_token			*lexer(const char *line);

// Lexer utils
t_token			*create_token(char *value, t_token_type type);
t_token			*get_last_token(t_token *token);
void			append_token(t_token **head, t_token *new_token);
void			remove_token(t_token **head, t_token *token);
char			**lex_split(const char *str);
size_t			lex_count_words(char const *str);
void			toggle_quote_state(char c, int *inside_s_quotes,
					int *inside_d_quotes);
t_token			*array2linked_list(char **array);
int				count_expansion_chars(const char *str);

// Expander
t_token			*expand(t_token *tokens, t_shell **shell);
char			*expand_word(char *word, t_shell *shell);
char			*hd_expand_word_stop_word(char *word, t_shell *shell);
void			print_tree(t_tree_node *node, int depth, int is_last);
void			process_nodes(t_tree_node *root, t_shell *shell);
void			hd_process_nodes(t_tree_node *root, t_shell *shell);
void			merge_tree_nodes(t_tree_node *root, char **expanded);
t_tree_node		*build_word_tree(char *word, t_shell *shell);
char			*replace_var(char *str, char *var, char *value);
void			substitute_variable_value(t_tree_node *root, t_shell *shell,
					char *dollar_sign);

// Build word tree
void			handle_normal_word(t_parse_state *state);
int				handle_variable_expansion(t_parse_state *state);

// Build word tree utils
int				is_special_character(char c, int in_dquotes);
int				len_until_special_character(char *str);
char			*process_quotes(t_parse_state *state);

// Tree node
t_tree_node		*create_tree_node(const char *value);
t_tree_node		*get_last_child(t_tree_node *node);
void			append_child(t_tree_node **head, t_tree_node *new_node);

// Tree utils
int				are_empty_quotes(const char *word);
int				count_quotes(char *word);
int				count_dollars(char *word);
int				is_expansion_done(char *word);

// Parser
t_cmd_node		*parse(t_token *tokens, t_shell **shell);

// Parser utils
t_cmd_node		*create_cmd_node(void);
void			append_cmd_node(t_cmd_node **head, t_cmd_node **new_node);
void			add_cmd(t_cmd_node **head, t_token *token);
void			add_file(t_cmd_node **head, t_token *token);
t_token			*move_forward_n(t_token *token, int n);
int				get_words_chain_len(t_token *token);
char			**linked_list2array(t_token *tokens);
int				len_cmds_lst(t_cmd_node *cmds);
t_cmd_node		*get_last_node(t_cmd_node *head);
void			set_error_status(t_shell **shell, char *error_msg);
int				is_valid_pipe_token(t_token *token);
int				is_valid_io_token(t_token *token);
int				is_misuse_case(t_token *token);
int				process_pipe_token(t_cmd_node **head, t_token **current_token);
void			process_word_token(t_cmd_node **head, t_token **current_token);
void			process_redirection_token(t_cmd_node **head,
					t_token **current_token);
int				is_redirection_token(t_token *token);
void			finalize_cmds_lst(t_cmd_node **head);
int				is_valid_pipe_token(t_token *token);
t_token			*detach_token(t_token *target, int size);

// Parser errors
int				check_tokens(t_token *tokens, t_shell **shell);
int				check_cmds(t_cmd_node *cmds, t_shell **shell);

// Utils
int				len_tokens_lst(t_token *tokens);
int				unbalanced_quotes(const char *str);
void			init_shell(t_shell **shell, char **env);
int				count_quotes(char *word);
t_token			*handle_standalone_redirections(t_token *tokens,
					t_shell **shell);
int				is_standalone_input_redirection(t_token *current, t_token *prev,
					t_token *next);
int				is_standalone_output_redirection(t_token *current,
					t_token *prev, t_token *next);

// Heredoc
void			heredoc_loop(t_heredoc *heredoc);
char			*generate_heredoc_filename(void);
char			*hd_expand_word(char *word, t_shell *shell);
int				set_heredoc_expansion_flag(t_token *tokens);
char			**ft_split_heredoc(const char *str);
int				count_segments(const char *str);

// Builtins
void			execute_builtins(char *path, char *args[], t_shell **shell);
char			*get_pwd(t_shell **shell);
int				pwd(t_shell **shell);
t_env			*get_env_lst(char **env);
char			*ft_getenv(char *key, t_shell *shell);
char			*get_env(char **env);
void			add_env_node(t_env **env_lst, char *entry);
void			update_env_node(t_env *node, char *new_value);
void			update_shlvl(t_shell **shell);
char			**env_lst_to_array(t_env *env_lst);
void			update_env_array(t_shell **shell);
void			print_env(t_shell *shell);
int				handle_too_many_arguments(char *args[], t_shell *shell);
void			handle_exit_error_message(t_shell **shell, char *message);
void			validate_exit_argument(char *arg, t_shell **shell);
void			ft_exit(char *args[], t_shell **shell);
int				are_only_digits(char *str);
int				len_args(char *args[]);
t_env			*find_node_by_key(char *key, t_shell *shell);
void			handle_cd_error(t_shell **shell, char *args[]);
void			update_pwds(t_shell **shell, char *old_pwd);
char			*get_cd_destination(char *args[], t_shell **shell);
void			cd(char *args[], t_shell **shell);
void			ft_unset(char *args[], t_shell **shell);
int				is_valid_key(char *key);
t_env			*last_node(t_env *env_lst);
int				is_builtin(char *cmd);

// Export
void			ft_exp_print(t_env *env_lst);
void			set_export_value_to_one(t_env **env_lst);
void			export_invalid_identifier(char *arg, t_shell **shell);
void			process_export_argument(char *arg, t_shell **shell);
void			ft_export(char *args[], t_shell **shell);
// Echo
void			ft_echo(char *args[], t_shell **shell);
int				get_n_flag(char *args[]);

// Memory
void			*free_till_n(char **result, size_t j);
void			free_if_not_in_gc(char *str);
void			free_all_split(char **split);
void			free_tokens(t_token *head);
void			free_cmds(t_cmd_node *head);
// t_exe	*parse_line(char *line, char **env);

#endif