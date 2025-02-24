/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:24:03 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/24 19:20:17 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_child_process(t_cmd_manager *cmd_manager, int chd_nbr)
{
	default_signals();
	if (chd_nbr == 0)
		handle_first_child(cmd_manager, chd_nbr);
	else if (chd_nbr == cmd_manager->nbr_cmds - 1)
		handle_last_child(cmd_manager, chd_nbr);
	else
		handle_mid_children(cmd_manager, chd_nbr);
	if (cmd_manager->cmds[chd_nbr].path == NULL
		&& cmd_manager->cmds[chd_nbr].fd_in > 2)
		exit(EXIT_SUCCESS);
	if (cmd_manager->cmds[chd_nbr].path == NULL
		|| cmd_manager->cmds[chd_nbr].fd_in == -1)
		command_error_handler(&cmd_manager->cmds[chd_nbr], cmd_manager->shell);
	execute_command(&cmd_manager->cmds[chd_nbr], cmd_manager->shell);
}

void	execute_command(t_command *cmd, t_shell **shell)
{
	if (is_builtin(cmd->path))
	{
		execute_builtins(cmd->path, cmd->args, shell);
		exit(EXIT_SUCCESS);
	}
	if (execve(cmd->path, cmd->args, (*shell)->env) == -1)
	{
		(*shell)->exit_status = COMMAND_NOT_FOUND;
		exit(COMMAND_NOT_FOUND);
	}
}

void	handle_parent_process(t_cmd_manager *cmd_manager)
{
	int	status;

	if (cmd_manager->nbr_cmds == 1)
	{
		waitpid(cmd_manager->pid, &status, 0);
		if (WIFEXITED(status))
			(*(cmd_manager->shell))->exit_status = status >> 8 & 0xFF;
		setup_signals();
	}
	else
		setup_signals();
}

int	handle_single_builtin(t_cmd_manager *cmd_manager, int *chd_nbr)
{
	if (cmd_manager->cmds[*chd_nbr].path
		&& is_builtin(cmd_manager->cmds[*chd_nbr].path))
	{
		execute_builtins(cmd_manager->cmds[*chd_nbr].path,
			cmd_manager->cmds[*chd_nbr].args, cmd_manager->shell);
		(*chd_nbr)++;
		return (1);
	}
	return (0);
}
