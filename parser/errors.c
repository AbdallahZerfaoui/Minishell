/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:51:05 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/08 15:40:03 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_tokens(t_token *tokens, t_shell **shell)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE && !current->next)
		{
			ft_putstr_fd(STDERR, "minishell: syntax error - expected a token after '|'");
			(*shell)->exit_status = MISUSE_ERROR;
			exit(MISUSE_ERROR);
		}
		else if (current->type == INFILE
			&& (!current->next || current->next->type != WORD))
		{
			ft_putstr_fd(STDERR, "minishell: syntax error after '<'");
			(*shell)->exit_status = MISUSE_ERROR;
			exit(MISUSE_ERROR);
		}
		else if (current->type == OUTFILE
			&& (!current->next || current->next->type != WORD))
		{
			ft_putstr_fd(STDERR, "minishell: syntax error after '>'");
			(*shell)->exit_status = MISUSE_ERROR;
			exit(MISUSE_ERROR);
		}
		current = current->next;
	}
}
