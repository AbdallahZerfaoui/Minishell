/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:31:49 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/20 23:32:42 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_fd_in(t_cmd_node *node)
{
	t_token	*current;
	int		fd_in;

	fd_in = STDIN_FILENO;
	current = node->files;
	while (current && current->next)
	{
		if (current->type == INFILE)
		{
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			if (access(current->next->value, F_OK) == -1)
				return (-1);
			fd_in = open(current->next->value, O_RDONLY);
		}
		current = current->next->next;
	}
	return (fd_in);
}

int	get_fd_out(t_cmd_node *node)
{
	t_token	*current;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	current = node->files;
	while (current && current->next)
	{
		if (current->type == OUTFILE)
		{
			if (fd_out != STDOUT_FILENO && fd_out != -1)
				close(fd_out);
			fd_out = open(current->next->value,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (current->type == APPEND)
		{
			if (fd_out != STDOUT_FILENO && fd_out != -1)
				close(fd_out);
			fd_out = open(current->next->value,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		current = current->next;
	}
	return (fd_out);
}
