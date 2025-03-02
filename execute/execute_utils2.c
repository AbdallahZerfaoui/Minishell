/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:27:46 by azerfaou          #+#    #+#             */
/*   Updated: 2025/03/02 15:47:46 by azerfaou         ###   ########.fr       */
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
	while (i < cmd_manager->nbr_cmds - 1)
	{
		wait(&status);
		i++;
	}
}
