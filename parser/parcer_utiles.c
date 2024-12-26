/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:15:40 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/26 21:36:12 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_node	*create_cmd_node(void)
{
	t_cmd_node	*new;

	new = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
	if (!new)
		return (NULL);
	return (new);
}

void	append_cmd_node(t_cmd_node **head, t_cmd_node *new_node)
{
	t_cmd_node	*last;

	if (!*head)
	{
		*head = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
		// return (new_node);
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	new_node->next = NULL;
	// return (head);
}

void	add_cmd(t_cmd_node **head, t_token *token)
{
	t_cmd_node	*current;

	current = *head;

	while (current->next)
		current = current->next;
	append_token(&current->cmd, token);
}

void	add_file(t_cmd_node **head, t_token *token)
{
	t_cmd_node	*current;

	current = *head;
	while (current->next)
		current = current->next;
	append_token(&current->files, token);
}
