/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:00:35 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/31 22:49:39 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	if (!head)
		return ;
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
