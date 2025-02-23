/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:31:12 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 21:25:58 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FORK_ERROR 127
# define CHILD_PROCESS 0
# define PIPE_ERROR 1
# define OPEN_ERROR 1
# define COMMAND_NOT_EXECUTABLE 126
# define ARGUMENT_ERROR 1
# define MALLOC_ERROR 1
# define COMMAND_NOT_FOUND 127
# define HEREDOC_ERROR 1
# define MISUSE_ERROR 2
# define ZERO 0

# include "../minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// char	*find_command_path(char *cmd);
void			close_unused_pipes(int **pipes, int nbr_cmds, int chd_nbr);
char			*get_command_path(char *cmd, char **env);
void			get_commands(char **argv, t_cmd_manager *cmd_manager);
void			handle_arguments(int argc);
void			initialize_pipes(t_cmd_manager *cmd_manager);
void			open_files(int argc, char **argv, t_cmd_manager *cmd_manager);
void			wait_for_children(t_cmd_manager *cmd_manager);
void			close_pipes(t_cmd_manager *cmd_manager);

// Handle children
void			handle_first_child(t_cmd_manager *cmd_manager, int chd_nbr);
void			handle_last_child(t_cmd_manager *cmd_manager, int chd_nbr);
void			handle_mid_children(t_cmd_manager *cmd_manager, int chd_nbr);

// Handle children utils
void			check_fds(int fd_in, int fd_out, t_shell **shell);
void			setup_input(int fd_in, char *hd_filename, int pipe_fd);
void			setup_output(int fd_out, int pipe_fd);

// Main
void			create_cmd_processes(t_cmd_manager *cmd_manager);
void			free_cmd_manager(t_cmd_manager *cmd_manager);

// Execute
void			execute(t_cmd_manager *cmd_manager);
void			handle_child_process(t_cmd_manager *cmd_manager, int chd_nbr);
void			handle_parent_process(t_cmd_manager *cmd_manager);
void			execute_command(t_command *cmd, t_shell **shell);
int				handle_single_builtin(t_cmd_manager *cmd_manager, int *chd_nbr);
int				handle_single_command(t_command *cmd, t_shell **shell);
void			fork_error_handler(t_shell **shell);
void			command_error_handler(t_command *cmd, t_shell **shell);

#endif
