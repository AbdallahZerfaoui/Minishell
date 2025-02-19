/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:04:47 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/19 19:54:31 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"
#include "../minishell.h"


// void	free_cmd_manager(t_cmd_manager *cmd_manager)
// {
// 	int	i;

// 	i = 0;
// 	while (i < cmd_manager->nbr_cmds)
// 	{
// 		free_all(cmd_manager->cmds[i].args);
// 		free(cmd_manager->cmds[i].path);
// 		i++;
// 	}
// 	free(cmd_manager->cmds);
// 	i = 0;
// 	while (i < cmd_manager->nbr_cmds - 1)
// 	{
// 		free(cmd_manager->pipes[i]);
// 		i++;
// 	}
// 	free(cmd_manager->pipes);
// }

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

/**
 * the parent process will loop and create nbr_cmds children
 * one for each command
 * the first child will read from the input file and write to the pipe
 * the last child will read from the pipe and write to the output file
 * the middle children will read from the pipe and write to the next one
 */
void	create_cmd_processes(t_cmd_manager *cmd_manager)
{
	int	chd_nbr;
	int	status;

	chd_nbr = 0;
	while (chd_nbr < cmd_manager->nbr_cmds)
	{
		// ignore_signals();
		if (cmd_manager->nbr_cmds == 1)
		{
			if (cmd_manager->cmds[chd_nbr].path == NULL)
			{
				// printf("im here\n");
				ft_putstr_fd(STDERR_FILENO, "bash: : command not found\n");
				(*(cmd_manager->shell))->exit_status = COMMAND_NOT_FOUND;
				break ;
			}
			else if (cmd_manager->cmds[chd_nbr].fd_in == -1)
			{
				ft_putstr_fd(STDERR_FILENO, "bash: :No such file or directory\n");
				(*(cmd_manager->shell))->exit_status = OPEN_ERROR;
				break ;
			}
			else if (cmd_manager->cmds[chd_nbr].path
				&& is_builtin(cmd_manager->cmds[chd_nbr].path))
			{
				execute_builtins(cmd_manager->cmds[chd_nbr].path,
					cmd_manager->cmds[chd_nbr].args,
					cmd_manager->shell);
				chd_nbr++;
				continue ;
			}
		}
		// else if (cmd_manager->nbr_cmds == 1
		// 	&& cmd_manager->cmds[chd_nbr].path)
		// {
		// 	if (execve(cmd_manager->cmds[chd_nbr].path,
		// 				cmd_manager->cmds[chd_nbr].args, (*(cmd_manager->shell))->env) == -1)
		// 	{
		// 		(*(cmd_manager->shell))->exit_status = COMMAND_NOT_FOUND;
		// 	}
		// }
		// else
		// {
		// default_child_signals();
		cmd_manager->pid = fork();
		if (cmd_manager->pid == -1)
		{
			ft_putstr_fd(STDERR_FILENO, "bash: fork error\n");
			(*(cmd_manager->shell))->exit_status = FORK_ERROR;
			exit(FORK_ERROR);
		}
		if (cmd_manager->pid == 0) // 0 is the child
		{
			default_signals();
			if (chd_nbr == 0)
				handle_first_child(cmd_manager, chd_nbr);
			else if (chd_nbr == cmd_manager->nbr_cmds - 1)
				handle_last_child(cmd_manager, chd_nbr);
			else
				handle_mid_children(cmd_manager, chd_nbr);
			// handle_mid_children(cmd_manager, chd_nbr && cmd_manager->nbr_cmds > 2);
			// printf("command : %c\n", cmd_manager->cmds[chd_nbr].path[0]);
			// printf("command : %s\n", cmd_manager->cmds[chd_nbr].path);
			//handle the case fd_in == -1
			if (cmd_manager->cmds[chd_nbr].path == NULL)
			{
				ft_putstr_fd(STDERR_FILENO, "bash: : command not found\n");
				(*(cmd_manager->shell))->exit_status = COMMAND_NOT_FOUND;
				exit(COMMAND_NOT_FOUND);
			}
			else if (cmd_manager->cmds[chd_nbr].fd_in == -1)
			{
				ft_putstr_fd(STDERR_FILENO, "bash: :No such file or directory\n");
				(*(cmd_manager->shell))->exit_status = OPEN_ERROR;
				exit(OPEN_ERROR);
			}
			else if (is_builtin(cmd_manager->cmds[chd_nbr].path))
			{
				execute_builtins(cmd_manager->cmds[chd_nbr].path,
					cmd_manager->cmds[chd_nbr].args,
					cmd_manager->shell);
				exit(EXIT_SUCCESS);
			}
			else if (execve(cmd_manager->cmds[chd_nbr].path,
					cmd_manager->cmds[chd_nbr].args, (*(cmd_manager->shell))->env) == -1)
			{
				(*(cmd_manager->shell))->exit_status = COMMAND_NOT_FOUND;
				// exit(COMMAND_NOT_FOUND);
				// if (errno == ENOENT)  //TODO should i keep this??
				// {
				// 	// printf("im here\n");
				// 	(*(cmd_manager->shell))->exit_status = ARGUMENT_ERROR;
				// 	// printf("exit status_pipex = %d\n", (*(cmd_manager->shell))->exit_status);
				// 	exit(ARGUMENT_ERROR);
				// }
				// else
				// {
				// 	// printf("im here in else\n");
				// 	(*(cmd_manager->shell))->exit_status = COMMAND_NOT_FOUND;
				// 	exit(COMMAND_NOT_FOUND);
				// }
			}
			else//TODO should i keep this??
			{
				(*(cmd_manager->shell))->exit_status = 0;
				// exit(EXIT_SUCCESS);
			}
		}
		else if (cmd_manager->nbr_cmds == 1)
		{
			waitpid(cmd_manager->pid, &status, 0);
			setup_signals();
		}
		else
		{
			setup_signals();
		}
		chd_nbr++;
	}
// if (cmd_manager->nbr_cmds > 1)
// 	wait_for_children(cmd_manager);
// else
// {
// 	int	status = 0; //dont let this be uninitialized
// 	wait(&status);
// 	// status = status >> 8 & 0xFF;
// 	// if (WIFEXITED(status))
// 	if ((*(cmd_manager->shell))->exit_status == 0)
// 		(*(cmd_manager->shell))->exit_status = status >> 8 & 0xFF;
// 	// (*shell)->exit_status = status >> 8 & 0xFF;
// 	// else
// 	// 	(*shell)->exit_status = 17;
// }
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
}
