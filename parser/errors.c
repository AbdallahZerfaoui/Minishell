/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:51:05 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/27 17:04:47 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE && !current->next)
		{
			perror("minishell: syntax error - expected a token after '|'");
			exit(1);
		}
		else if (current->type == INFILE
			&& (!current->next || current->next->type != WORD))
		{
			perror("minishell: syntax error after '<'");
			exit(1);
		}
		else if (current->type == OUTFILE
			&& (!current->next || current->next->type != WORD))
		{
			perror("minishell: syntax error after '>'");
			exit(1);
		}
		current = current->next;
	}
}
