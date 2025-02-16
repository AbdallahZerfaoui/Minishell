/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:51:05 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/16 23:16:06 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_tokens(t_token *tokens, t_shell **shell)
{
	t_token		*current;
	// struct stat	sb;
	// char		*expanded;

	current = tokens;
	while (current)
	{
		// expanded = expand_word(current->value, *shell);
		if (current->type == PIPE
			&& (!current->next || !current->prev || current->next->type != WORD || current->prev->type != WORD))
		{
			ft_putstr_fd(STDERR_FILENO,
				"bash: syntax error near unexpected token `|'\n");
			(*shell)->exit_status = MISUSE_ERROR;
			return (MISUSE_ERROR);
		}
		else if (current->type == HEREDOC && !current->next)
		{
			ft_putstr_fd(STDERR_FILENO,
				"bash: syntax error near unexpected token `newline'\n");
			(*shell)->exit_status = MISUSE_ERROR;
			return (MISUSE_ERROR);
		}
		else if (current->type == INFILE
			&& (!current->next || current->next->type != WORD))
		{
			ft_putstr_fd(STDERR_FILENO, "bash: syntax error after '<'\n");
			(*shell)->exit_status = MISUSE_ERROR;
			return (MISUSE_ERROR);
		}
		else if (current->type == OUTFILE
			&& (!current->next || current->next->type != WORD))
		{
			ft_putstr_fd(STDERR_FILENO, "bash: syntax error after '>'\n");
			(*shell)->exit_status = MISUSE_ERROR;
			return (MISUSE_ERROR);
		}
		else if (current->type == APPEND
			&& (!current->next || current->next->type != WORD))
		{
			ft_putstr_fd(STDERR_FILENO, "bash: syntax error after '>>'\n");
			(*shell)->exit_status = MISUSE_ERROR;
			return (MISUSE_ERROR);
		}
		// else if ((stat(current->value, &sb) == 0 && S_ISDIR(sb.st_mode)))
		// {
		// 	ft_putstr_fd(STDERR_FILENO, "bash: ");
		// 	ft_putstr_fd(STDERR_FILENO, current->value);
		// 	ft_putstr_fd(STDERR_FILENO, ": is a directory\n");
		// 	(*shell)->exit_status = 126;
		// 	return (126);
		// }
		// else if ((stat(expanded, &sb) == 0 && S_ISDIR(sb.st_mode)))
		// {
		// 	ft_putstr_fd(STDERR_FILENO, "bash: ");
		// 	ft_putstr_fd(STDERR_FILENO, expanded);
		// 	ft_putstr_fd(STDERR_FILENO, ": is a directory\n");
		// 	(*shell)->exit_status = 126;
		// 	return (126);
		// }
		// else if (ft_strcmp(current->value, ".") == 0)
		// {
		// 	ft_putstr_fd(STDERR_FILENO, "bash: .: filename argument required\n");
		// 	(*shell)->exit_status = COMMAND_NOT_FOUND;
		// 	return (COMMAND_NOT_FOUND);
		// }
		// else if (ft_strcmp(current->value, "..") == 0)
		// {
		// 	ft_putstr_fd(STDERR_FILENO, "bash: ..: command not found\n");
		// 	(*shell)->exit_status = COMMAND_NOT_FOUND;
		// 	return (COMMAND_NOT_FOUND);
		// }
		current = current->next;
	}
	return (0);
}

int	check_cmds(t_cmd_node *cmds, t_shell **shell)
{
	t_cmd_node	*current;
	struct stat	sb;
	char		*cmd;

	current = cmds;
	while (current)
	{
		if (current->cmd_array && current->cmd_array[0])
		{
			cmd = current->cmd_array[0];
			if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
			{
				ft_putstr_fd(STDERR_FILENO, "bash: ");
				ft_putstr_fd(STDERR_FILENO, cmd);
				ft_putstr_fd(STDERR_FILENO, ": is a directory\n");
				(*shell)->exit_status = COMMAND_NOT_EXECUTABLE;
				return (COMMAND_NOT_EXECUTABLE);
			}
		}
		current = current->next;
	}
	return (0);
}
