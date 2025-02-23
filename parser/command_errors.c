/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 22:52:28 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 22:52:51 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cmds(t_cmd_node *cmds, t_shell **shell)
{
	t_cmd_node	*current;
	struct stat	sb;
	char		*cmd;

	current = cmds;
	while (current)
	{
		if (current->cmd_array && current->cmd_array[0])
		{
			cmd = current->cmd_array[0];
			if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
			{
				set_error_status(shell, "bash: ");
				set_error_status(shell, cmd);
				set_error_status(shell, ": is a directory\n");
				(*shell)->exit_status = COMMAND_NOT_EXECUTABLE;
				return (COMMAND_NOT_EXECUTABLE);
			}
		}
		current = current->next;
	}
	return (0);
}
