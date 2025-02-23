/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:49:36 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 22:10:31 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_first_child(t_cmd_manager *cmd_manager, int chd_nbr)
{
	int	fd_in;
	int	fd_out;

	fd_in = cmd_manager->cmds[chd_nbr].fd_in;
	fd_out = cmd_manager->cmds[chd_nbr].fd_out;
	check_fds(fd_in, fd_out, cmd_manager->shell);
	setup_input(fd_in, cmd_manager->cmds[chd_nbr].hd_filename, -1);
	if (cmd_manager->nbr_cmds > 1)
	{
		setup_output(fd_out, cmd_manager->pipes[chd_nbr][1]);
		close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	handle_last_child(t_cmd_manager *cmd_manager, int chd_nbr)
{
	int	fd_out;

	fd_out = cmd_manager->cmds[chd_nbr].fd_out;
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
	setup_input(cmd_manager->cmds[chd_nbr].fd_in,
		cmd_manager->cmds[chd_nbr].hd_filename, cmd_manager->pipes[chd_nbr
		- 1][0]);
	setup_output(fd_out, -1);
	cmd_manager->pid = getpid();
}

// TODO fix this shit NOW
void	handle_mid_children(t_cmd_manager *cmd_manager, int chd_nbr)
{
	int	fd_out;
	int	fd_in;

	fd_in = cmd_manager->cmds[chd_nbr].fd_in;
	fd_out = cmd_manager->cmds[chd_nbr].fd_out;
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
	setup_input(fd_in, cmd_manager->cmds[chd_nbr].hd_filename,
		cmd_manager->pipes[chd_nbr - 1][0]);
	setup_output(fd_out, cmd_manager->pipes[chd_nbr][1]);
}
