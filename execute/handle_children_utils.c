/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_children_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:12:54 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 22:16:36 by azerfaou         ###   ########.fr       */
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

void	setup_input(int fd_in, char *hd_filename, int pipe_fd)
{
	int	hd_fd;

	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (hd_filename != NULL && hd_filename[0] != '\0')
	{
		hd_fd = open(hd_filename, O_RDONLY);
		if (hd_fd < 0)
		{
			perror("open hd_filename");
			exit(EXIT_FAILURE);
		}
		dup2(hd_fd, STDIN_FILENO);
		close(hd_fd);
	}
	else if (pipe_fd >= 0)
	{
		dup2(pipe_fd, STDIN_FILENO);
		close(pipe_fd);
	}
}

// Helper to set up output redirection
void	setup_output(int fd_out, int pipe_fd)
{
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (pipe_fd >= 0)
	{
		dup2(pipe_fd, STDOUT_FILENO);
		close(pipe_fd);
	}
}
