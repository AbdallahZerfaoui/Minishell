/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:49:36 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/21 16:36:58 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_fds(int fd_in, int fd_out, t_shell **shell)
{
	if (fd_in == -1 || fd_out == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "bash: :No such file or directory\n");
		(*shell)->exit_status = OPEN_ERROR;
		exit(OPEN_ERROR);
	}
}

void	handle_first_child(t_cmd_manager *cmd_manager, int chd_nbr)
{
	int	fd_in;
	int	fd_out;
	int	hd_fd;

	fd_in = cmd_manager->cmds[chd_nbr].fd_in;
	fd_out = cmd_manager->cmds[chd_nbr].fd_out;
	// TODO maybe i should change the input of check_fds to take cmd_manager directly
	check_fds(fd_in, fd_out, cmd_manager->shell);
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd_manager->cmds[chd_nbr].hd_filename != NULL
		&& cmd_manager->cmds[chd_nbr].hd_filename[0] != '\0')
	{
		hd_fd = open(cmd_manager->cmds[chd_nbr].hd_filename, O_RDONLY);
		unlink(cmd_manager->cmds[chd_nbr].hd_filename);
		if (hd_fd < 0)
		{
			perror("open hd_filename");
			exit(EXIT_FAILURE);
		}
		dup2(hd_fd, STDIN_FILENO);
		close(hd_fd);
	}
	else if (cmd_manager->nbr_cmds > 1)
	{
		dup2(cmd_manager->pipes[chd_nbr][1], STDOUT_FILENO);
		close(cmd_manager->pipes[chd_nbr][1]);
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
	int	hd_fd;

	fd_out = cmd_manager->cmds[chd_nbr].fd_out;
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
	if (cmd_manager->cmds[chd_nbr].hd_filename != NULL
		&& cmd_manager->cmds[chd_nbr].hd_filename[0] != '\0')
	{
		hd_fd = open(cmd_manager->cmds[chd_nbr].hd_filename, O_RDONLY);
		unlink(cmd_manager->cmds[chd_nbr].hd_filename);
		if (hd_fd < 0)
		{
			perror("open hd_filename");
			exit(EXIT_FAILURE);
		}
		dup2(hd_fd, STDIN_FILENO);
		close(hd_fd);
	}
	else if (cmd_manager->cmds[chd_nbr].fd_in > 0)
	{
		dup2(cmd_manager->cmds[chd_nbr].fd_in, STDIN_FILENO);
		close(cmd_manager->cmds[chd_nbr].fd_in);
	}
	else
	{
		dup2(cmd_manager->pipes[chd_nbr - 1][0], STDIN_FILENO);
		close(cmd_manager->pipes[chd_nbr - 1][0]);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	cmd_manager->pid = getpid();
}

void	handle_mid_children(t_cmd_manager *cmd_manager, int chd_nbr)
		// TODO fix this shit NOW
{
	int fd_out = cmd_manager->cmds[chd_nbr].fd_out;
	int	hd_fd;

	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);

	// Handle input
	if (cmd_manager->cmds[chd_nbr].fd_in > 0)
	{
		dup2(cmd_manager->cmds[chd_nbr].fd_in, STDIN_FILENO);
		close(cmd_manager->cmds[chd_nbr].fd_in);
	}
	else
	{
		dup2(cmd_manager->pipes[chd_nbr - 1][0], STDIN_FILENO);
		close(cmd_manager->pipes[chd_nbr - 1][0]);
	}

	// Handle output
	if (cmd_manager->cmds[chd_nbr].hd_filename != NULL)
	{
		hd_fd = open(cmd_manager->cmds[chd_nbr].hd_filename, O_RDONLY);
		dup2(hd_fd, STDIN_FILENO);
		close(hd_fd);
	}
	else if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
	{
		dup2(cmd_manager->pipes[chd_nbr][1], STDOUT_FILENO);
		close(cmd_manager->pipes[chd_nbr][1]);
	}
}
