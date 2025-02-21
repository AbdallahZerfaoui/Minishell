/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:21:17 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/21 22:07:00 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_cmd_manager *cmd_manager)
{
	int	chd_nbr;

	chd_nbr = 0;
	while (chd_nbr < cmd_manager->nbr_cmds)
	{
		if (cmd_manager->nbr_cmds == 1)
		{
			if (handle_single_command(&cmd_manager->cmds[chd_nbr],
					cmd_manager->shell))
				break ;
			if (handle_single_builtin(cmd_manager, chd_nbr))
			{
				chd_nbr++;
				continue ;
			}
		}
		cmd_manager->pid = fork();
		if (cmd_manager->pid == -1)
			fork_error_handler(cmd_manager->shell);
		if (cmd_manager->pid == 0)
			handle_child_process(cmd_manager, chd_nbr);
		else
			handle_parent_process(cmd_manager);
		chd_nbr++;
	}
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
}
