/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:49:36 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/28 23:57:47 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"
#include "../minishell.h"

// int	get_fd_in(t_cmd_manager *cmd_manager, int chd_nbr)
// {
// 	t_cmd_node	*current;
// 	int			fd_in;

// 	fd_in = STDIN_FILENO;
// 	current = cmd_manager->cmds_lst;
// 	if (!current)
// 		return (fd_in);
// 	while (current->index != chd_nbr)
// 		current = current->next;
// 	if (current && current->files && current->files->type == INFILE)
// 	{
// 		// printf("current->files[1].value = %\n", &current);
// 		fd_in = open(current->files->value, O_RDONLY);
// 		if (fd_in == -1)
// 		{
// 			perror("open");
// 			exit(OPEN_ERROR);
// 		}
// 	}
// 	return (fd_in);
// }

// int	get_fd_out(t_cmd_manager *cmd_manager, int chd_nbr)
// {
// 	t_cmd_node	*current;
// 	int			fd_out;
// 	t_token		*file;

// 	fd_out = STDOUT_FILENO;
// 	current = cmd_manager->cmds_lst;
// 	if (!current)
// 		return (fd_out);
// 	while (current->index != chd_nbr)
// 		current = current->next;
// 	if (current && current->files && current->files->type == OUTFILE)
// 	{
// 		file = current->files->next;
// 		printf("current->files[1].value = %s\n", file->value);
// 		fd_out = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd_out == -1)
// 		{
// 			perror("open");
// 			exit(OPEN_ERROR);
// 		}
// 	}
// 	return (fd_out);
// }

void	handle_first_child(t_cmd_manager *cmd_manager, int chd_nbr)
{
	// int	fd_in;
	// int	fd_out;

	// fd_in = get_fd_in(cmd_manager, chd_nbr);
	// fd_out = get_fd_out(cmd_manager, chd_nbr);
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
	dup2(cmd_manager->pipes[chd_nbr][1], STDOUT_FILENO);
	close(cmd_manager->pipes[chd_nbr][1]);
	// printf("fd_in = %d\n", fd_in);
	// printf("fd_out = %d\n", fd_out);
	// if (fd_out != STDOUT_FILENO)
	// {
	// 	dup2(fd_out, STDOUT_FILENO);
	// 	close(fd_out);
	// }
}

void	handle_last_child(t_cmd_manager *cmd_manager, int chd_nbr)
{
	// int	fd_in;
	// int	fd_out;

	// fd_in = get_fd_in(cmd_manager, chd_nbr);
	// fd_out = get_fd_out(cmd_manager, chd_nbr);
	// printf("fd_in = %d\n", fd_in);
	// printf("fd_out = %d\n", fd_out);
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
	dup2(cmd_manager->pipes[chd_nbr - 1][0], STDIN_FILENO);
	close(cmd_manager->pipes[chd_nbr - 1][0]);
	// printf("fd_in = %d\n", fd_in);
	// printf("fd_out = %d\n", fd_out);
	// if (fd_out != STDOUT_FILENO)
	// {
	// 	dup2(fd_out, STDOUT_FILENO);
	// 	close(fd_out);
	// }
}

void	handle_mid_children(t_cmd_manager *cmd_manager, int chd_nbr)
{
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
	dup2(cmd_manager->pipes[chd_nbr - 1][0], STDIN_FILENO);
	close(cmd_manager->pipes[chd_nbr - 1][0]);
	dup2(cmd_manager->pipes[chd_nbr][1], STDOUT_FILENO);
	close(cmd_manager->pipes[chd_nbr][1]);
}
