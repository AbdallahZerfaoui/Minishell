/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:21:17 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/26 23:54:06 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO it would be better if you handle
// execution based on being last command or not
void	execute(t_cmd_manager *cmd_manager)
{
	int	chd_nbr;

	chd_nbr = 0;
	while (chd_nbr < cmd_manager->nbr_cmds)
	{
		if (cmd_manager->nbr_cmds == 1)
		{
			if (handle_single_builtin(cmd_manager, &chd_nbr))
				break ;
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
