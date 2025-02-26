/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:04:47 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/26 23:06:15 by azerfaou         ###   ########.fr       */
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
	while (i < nbr_cmds - 1)
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
