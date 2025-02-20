/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:27:46 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/20 22:08:07 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * This function checks if a command is a builtin
 */
int	is_builtin(char *cmd)
{
	static char	*builtins[] = {"pwd", "cd", "env", "exit", "unset", "export",
		"echo", NULL};
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	initialize_pipes(t_cmd_manager *cmd_manager)
{
	int	i;

	i = 0;
	cmd_manager->pipes = (int **)ft_calloc((cmd_manager->nbr_cmds - 1),
			sizeof(int *));
	if (!cmd_manager->pipes)
		exit(MALLOC_ERROR);
	while (i < cmd_manager->nbr_cmds - 1)
	{
		cmd_manager->pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(cmd_manager->pipes[i]) == -1)
			exit(PIPE_ERROR);
		i++;
	}
}

/**
 * This function close the pipes that are not used by the child
 * @param nbr_cmds the number of commands
 * @note every wait() call will wait till one child is done
 * after nbr_cmds calls to wait() all the children will be done
 */
void	wait_for_children(t_cmd_manager *cmd_manager)
{
	int		status;
	int		i;
	pid_t	last_pid;

	i = 0;
	last_pid = cmd_manager->pid;
	waitpid(last_pid, &status, 0);
	(*(cmd_manager->shell))->exit_status = status >> 8 & 0xFF;
		// TODO understand it
	while (i < cmd_manager->nbr_cmds - 1)
	{
		wait(&status);
		i++;
	}
}
