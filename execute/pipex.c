/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:04:47 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/22 19:00:57 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * This function closes the unused pipes
 * if i != chd_nbr - 1, close the read end
 * if i != chd_nbr, close the write end
 * @note need to handle errors of close
 */
void	close_unused_pipes(int **pipes, int nbr_cmds, int chd_nbr)
{
	int	i;

	i = 0;
	while (i < nbr_cmds - 1) //TODO check the case i =0 ch =1
	{
		if (i != chd_nbr - 1)
		{
			close(pipes[i][0]);
		}
		if (i != chd_nbr)
		{
			close(pipes[i][1]);
		}
		i++;
	}
}

/**
 * This function closes the pipes
 * @param cmd_manager the structure containing the pipes
 * it closes every pipe
 * 0 is the read end
 * 1 is the write end
 */
void	close_pipes(t_cmd_manager *cmd_manager)
{
	int	i;

	i = 0;
	while (i < cmd_manager->nbr_cmds - 1)
	{
		close(cmd_manager->pipes[i][1]);
		close(cmd_manager->pipes[i][0]);
		i++;
	}
}

int	handle_single_command(t_command *cmd, t_shell **shell)
{
	if (cmd->path == NULL
		&& cmd->fd_in > 2)
		return (1);
	else if (cmd->hd_filename != NULL)
		return (1);
	else if (cmd->path == NULL)
	{
		ft_putstr_fd(STDERR_FILENO, "bash:");
		ft_putstr_fd(STDERR_FILENO, ": command not found\n");
		(*shell)->exit_status = COMMAND_NOT_FOUND;
		return (1);
	}
	else if (cmd->fd_in == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "bash: :No such file or directory\n");
		(*shell)->exit_status = OPEN_ERROR;
		return (1);
	}
	return (0);
}

/**
 * the parent process will loop and create nbr_cmds children
 * one for each command
 * the first child will read from the input file and write to the pipe
 * the last child will read from the pipe and write to the output file
 * the middle children will read from the pipe and write to the next one
 */
// void	create_cmd_processes(t_cmd_manager *cmd_manager)
// {
// 	int	chd_nbr;
// 	int	status;

// 	chd_nbr = 0;
// 	while (chd_nbr < cmd_manager->nbr_cmds)
// 	{
// 		if (cmd_manager->nbr_cmds == 1)
// 		{
// 			if (handle_single_command
// 				(&cmd_manager->cmds[chd_nbr], cmd_manager->shell))
// 				break ;
// 			if (cmd_manager->cmds[chd_nbr].path
// 				&& is_builtin(cmd_manager->cmds[chd_nbr].path))
// 			{
// 				execute_builtins(cmd_manager->cmds[chd_nbr].path,
// 					cmd_manager->cmds[chd_nbr].args,
// 					cmd_manager->shell);
// 				chd_nbr++;
// 				continue ;
// 			}
// 		}
// 		cmd_manager->pid = fork();
// 		if (cmd_manager->pid == -1)
// 		{
// 			ft_putstr_fd(STDERR_FILENO, "bash: fork error\n");
// 			(*(cmd_manager->shell))->exit_status = FORK_ERROR;
// 			exit(FORK_ERROR);
// 		}
// 		if (cmd_manager->pid == 0) // 0 is the child
// 		{
// 			default_signals();
// 			if (chd_nbr == 0)
// 				handle_first_child(cmd_manager, chd_nbr);
// 			else if (chd_nbr == cmd_manager->nbr_cmds - 1)
// 				handle_last_child(cmd_manager, chd_nbr);
// 			else
// 				handle_mid_children(cmd_manager, chd_nbr);
// 			if (cmd_manager->cmds[chd_nbr].path == NULL
// 				&& cmd_manager->cmds[chd_nbr].fd_in > 2)
// 			{
// 				exit(EXIT_SUCCESS);
// 			}
// 			if (cmd_manager->cmds[chd_nbr].path == NULL)
// 			{
// 				ft_putstr_fd(STDERR_FILENO, "bash:zzzz");
// 				ft_putstr_fd(STDERR_FILENO, ": command not found\n");
// 				(*(cmd_manager->shell))->exit_status = COMMAND_NOT_FOUND;
// 				exit(COMMAND_NOT_FOUND);
// 			}
// 			else if (cmd_manager->cmds[chd_nbr].fd_in == -1)
// 			{
// 				ft_putstr_fd(STDERR_FILENO, "bash: :No such file or directory\n");
// 				(*(cmd_manager->shell))->exit_status = OPEN_ERROR;
// 				exit(OPEN_ERROR);
// 			}
// 			else if (is_builtin(cmd_manager->cmds[chd_nbr].path))
// 			{
// 				execute_builtins(cmd_manager->cmds[chd_nbr].path,
// 					cmd_manager->cmds[chd_nbr].args,
// 					cmd_manager->shell);
// 				exit(EXIT_SUCCESS);
// 			}
// 			else if (execve(cmd_manager->cmds[chd_nbr].path,
// 					cmd_manager->cmds[chd_nbr].args, (*(cmd_manager->shell))->env) == -1)
// 			{
// 				(*(cmd_manager->shell))->exit_status = COMMAND_NOT_FOUND;
// 			}
// 			else//TODO should i keep this??
// 			{
// 				(*(cmd_manager->shell))->exit_status = 0;
// 			}
// 		}
// 		else if (cmd_manager->nbr_cmds == 1)
// 		{
// 			waitpid(cmd_manager->pid, &status, 0);
// 			if (WIFEXITED(status))
// 				(*(cmd_manager->shell))->exit_status = status >> 8 & 0xFF;
// 			setup_signals();
// 		}
// 		else
// 		{
// 			setup_signals();
// 		}
// 		chd_nbr++;
// 	}
// 	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
// }
