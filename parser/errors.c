/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:51:05 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/16 22:00:47 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_tokens(t_token *tokens, t_shell **shell)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
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
		// else if (ft_strcmp(current->value, "~") == 0)
		// {
		// 	ft_putstr_fd(STDERR_FILENO, "bash: ~: is a directory\n");
		// 	(*shell)->exit_status = 126;
		// 	return (126);
		// }
		// else if (ft_strcmp(current->value, "/") == 0)
		// {
		// 	ft_putstr_fd(STDERR_FILENO, "bash: /: is a directory\n");
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
