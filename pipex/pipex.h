/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:37:12 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/28 21:36:16 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FORK_ERROR 127
# define CHILD_PROCESS 0
# define PIPE_ERROR 127
# define OPEN_ERROR 127
// # define EXIT_FAILURE 127
# define ARGUMENT_ERROR 127
# define MALLOC_ERROR 127

# include "../minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// typedef struct s_command
// {
// 	char		*path;
// 	char		**args;
// }				t_command;

// typedef struct s_cmd_manager
// {
// 	int			nbr_cmds;
// 	int			**pipes;
// 	int			fd_in;
// 	int			fd_out;
// 	t_command	*cmds;
// 	pid_t		pid;
// 	char		**env;
// }				t_cmd_manager;

// Libft functions
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
void			*free_all(char **result);
char			*ft_strdup(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *s);
void			*ft_calloc(size_t nitems, size_t size);

// char	*find_command_path(char *cmd);
void			close_unused_pipes(int **pipes, int nbr_cmds, int chd_nbr);
char			*get_command_path(char *cmd, char **env);
void			get_commands(char **argv, t_cmd_manager *cmd_manager);
void			handle_arguments(int argc);
void			initialize_pipes(t_cmd_manager *cmd_manager);
void			open_files(int argc, char **argv, t_cmd_manager *cmd_manager);
void			wait_for_children(int nbr_cmds);
void			close_pipes(t_cmd_manager *cmd_manager);

// Handle children
void			handle_first_child(t_cmd_manager *cmd_manager, int chd_nbr);
void			handle_last_child(t_cmd_manager *cmd_manager, int chd_nbr);
void			handle_mid_children(t_cmd_manager *cmd_manager, int chd_nbr);

// Main
void			create_cmd_processes(t_cmd_manager *cmd_manager);
void			free_cmd_manager(t_cmd_manager *cmd_manager);

#endif
