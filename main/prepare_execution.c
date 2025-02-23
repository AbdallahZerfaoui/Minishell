/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:33:21 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 22:24:30 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_heredocs(t_cmd_node *cmds, t_cmd_manager *cmd_manager,
		t_shell **shell)
{
	t_cmd_node	*current;
	t_token		*file;
	t_heredoc	*heredoc;
	char		*hd_filename;
	int			i;

	current = cmds;
	i = 0;
	while (current)
	{
		file = current->files;
		while (file)
		{
			if (file->type == HEREDOC && file->next)
			{
				hd_filename = generate_heredoc_filename();
				heredoc = init_heredoc_struct(file->next->value, hd_filename,
						shell);
				heredoc_loop(heredoc);
				cmd_manager->cmds[i].hd_filename = heredoc->filename;
			}
			file = file->next;
		}
		i++;
		current = current->next;
	}
}

t_cmd_manager	*prepare_execution(t_cmd_node *cmds, t_shell **shell)
{
	t_cmd_manager	*cmd_manager;
	t_cmd_node		*current;
	int				i;
	char			*custom_cmd_path;

	cmd_manager = (t_cmd_manager *)ft_calloc(1, sizeof(t_cmd_manager));
	if (!cmd_manager)
		return (NULL);
	cmd_manager->nbr_cmds = len_cmds_lst(cmds);
	cmd_manager->cmds = (t_command *)ft_calloc(cmd_manager->nbr_cmds,
			sizeof(t_command));
	if (!cmd_manager->cmds)
		return (NULL);
	process_heredocs(cmds, cmd_manager, shell);
	current = cmds;
	i = 0;
	while (current)
	{
		if (current->cmd_array && current->cmd_array[0])
		{
			custom_cmd_path = get_command_path(current->cmd_array[0],
					(*shell)->env);
			if (access(current->cmd_array[0], X_OK) == 0 && !custom_cmd_path)
				cmd_manager->cmds[i].path = ft_strdup(current->cmd_array[0]);
			else
				cmd_manager->cmds[i].path = custom_cmd_path;
			cmd_manager->cmds[i].args = current->cmd_array;
		}
		cmd_manager->cmds[i].fd_in = get_fd_in(current);
		cmd_manager->cmds[i].fd_out = get_fd_out(current);
		current = current->next;
		i++;
	}
	cmd_manager->shell = shell;
	cmd_manager->cmds_lst = cmds;
	return (cmd_manager);
}
