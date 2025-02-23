/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standalone_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:02:47 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 23:15:18 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_standalone_input_redirection(t_token *current, t_token *prev,
		t_token *next)
{
	return ((current->type == INFILE) && (!prev || prev->type != WORD) && (next
			&& next->type == WORD));
}

static int	is_standalone_output_redirection(t_token *current, t_token *prev,
		t_token *next)
{
	return ((current->type == OUTFILE || current->type == APPEND) && (!prev
			|| prev->type != WORD) && (next && next->type == WORD));
}

static int	handle_input_redirection(t_token *next, t_shell **shell)
{
	if (access(next->value, F_OK) == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "bash: ");
		ft_putstr_fd(STDERR_FILENO, next->value);
		ft_putstr_fd(STDERR_FILENO, ": No such file or directory\n");
		(*shell)->exit_status = OPEN_ERROR;
		return (0);
	}
	return (1);
}

static int	handle_output_redirection(t_token *next, t_shell **shell)
{
	int	tmp_fd;

	if (next->type == OUTFILE)
		tmp_fd = open(next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		tmp_fd = open(next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (tmp_fd < 0)
	{
		ft_putstr_fd(STDERR_FILENO, "bash: : open error\n");
		(*shell)->exit_status = OPEN_ERROR;
		return (0);
	}
	return (1);
}

t_token	*handle_standalone_redirections(t_token *tokens, t_shell **shell)
{
	t_token	*current;
	t_token	*next;
	t_token	*prev;

	current = tokens;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (is_standalone_output_redirection(current, prev, next))
		{
			if (!handle_output_redirection(next, shell))
				return (NULL);
			if (current->next->next)
			{
				tokens = current->next->next;
				if (tokens->type == PIPE)
					tokens = tokens->next;
			}
			else
				tokens = NULL;
			current = tokens;
			if (current && current->next)
				next = current->next;
		}
		else if (is_standalone_input_redirection(current, prev, next))
		{
			if (!handle_input_redirection(next, shell))
				return (NULL);
		}
		prev = current;
		current = next;
	}
	return (tokens);
}
