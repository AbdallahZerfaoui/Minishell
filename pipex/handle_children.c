/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:49:36 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/28 18:25:45 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_first_child(t_cmd_manager *cmd_manager, int chd_nbr)
{
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
	dup2(cmd_manager->pipes[chd_nbr][1], STDOUT_FILENO);
	close(cmd_manager->pipes[chd_nbr][1]);
}

void	handle_last_child(t_cmd_manager *cmd_manager, int chd_nbr)
{
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
	dup2(cmd_manager->pipes[chd_nbr - 1][0], STDIN_FILENO);
	close(cmd_manager->pipes[chd_nbr - 1][0]);
}

void	handle_mid_children(t_cmd_manager *cmd_manager, int chd_nbr)
{
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
	dup2(cmd_manager->pipes[chd_nbr - 1][0], STDIN_FILENO);
	close(cmd_manager->pipes[chd_nbr - 1][0]);
	dup2(cmd_manager->pipes[chd_nbr][1], STDOUT_FILENO);
	close(cmd_manager->pipes[chd_nbr][1]);
}
