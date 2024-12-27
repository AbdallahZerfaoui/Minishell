/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 22:40:05 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/27 16:39:12 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_tokens_lst(t_token *tokens)
{
	int		len;
	t_token	*current;

	len = 0;
	current = tokens;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_cmds(t_cmd_node *head)
{
	t_cmd_node	*current;
	t_cmd_node	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free_tokens(current->cmd);
		free_tokens(current->files);
		free(current);
		current = next;
	}
}
