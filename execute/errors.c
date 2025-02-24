/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:20:20 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/24 19:20:35 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_error_handler(t_command *cmd, t_shell **shell)
{
	if (cmd->path == NULL)
	{
		ft_putstr_fd(STDERR_FILENO, "bash: ");
		ft_putstr_fd(STDERR_FILENO, cmd->args[0]);
		ft_putstr_fd(STDERR_FILENO, ": command not found\n");
		(*shell)->exit_status = COMMAND_NOT_FOUND;
	}
	else if (cmd->fd_in == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "bash: No such file or directory\n");
		(*shell)->exit_status = OPEN_ERROR;
	}
	exit((*shell)->exit_status);
}

void	fork_error_handler(t_shell **shell)
{
	ft_putstr_fd(STDERR_FILENO, "bash: fork error\n");
	(*shell)->exit_status = FORK_ERROR;
	exit(FORK_ERROR);
}
