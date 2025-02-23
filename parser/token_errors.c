/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:51:05 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 23:04:06 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_pipe_token(t_token *token)
{
	return (token->next && token->prev
		&& token->next->type == WORD
		&& token->prev->type == WORD);
}

void	set_error_status(t_shell **shell, char *error_msg)
{
	ft_putstr_fd(STDERR_FILENO, error_msg);
	(*shell)->exit_status = MISUSE_ERROR;
}

int	is_valid_io_token(t_token *token)
{
	return (token->next && token->next->type == WORD);
}

int	is_misuse_case(t_token *token)
{
	return ((token->type == PIPE && !is_valid_pipe_token(token))
		|| (token->type == HEREDOC && !token->next)
		|| (token->type == INFILE && !is_valid_io_token(token))
		|| (token->type == OUTFILE && !is_valid_io_token(token))
		|| (token->type == APPEND && !is_valid_io_token(token)));
}

int	check_tokens(t_token *tokens, t_shell **shell)
{
	t_token		*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE && !is_valid_pipe_token(current))
			set_error_status(shell,
				"bash: syntax error near unexpected token `|'\n");
		else if (current->type == HEREDOC && !current->next)
			set_error_status(shell,
				"bash: syntax error near unexpected token `newline'\n");
		else if (current->type == INFILE && !is_valid_io_token(current))
			set_error_status(shell, "bash: syntax error after '<'\n");
		else if (current->type == OUTFILE && !is_valid_io_token(current))
			set_error_status(shell, "bash: syntax error after '>'\n");
		else if (current->type == APPEND && !is_valid_io_token(current))
			set_error_status(shell, "bash: syntax error after '>>'\n");
		if (is_misuse_case(current))
			return (MISUSE_ERROR);
		current = current->next;
	}
	return (0);
}
