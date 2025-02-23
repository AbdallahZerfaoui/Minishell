/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 22:56:14 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 22:59:30 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_node	*create_cmd_node(void)
{
	static int	index;
	t_cmd_node	*new;

	new = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
	if (!new)
		return (NULL);
	new->index = index;
	index++;
	return (new);
}

t_cmd_node	*get_last_node(t_cmd_node *head)
{
	t_cmd_node	*current;

	current = head;
	while (current->next)
		current = current->next;
	return (current);
}

void	append_cmd_node(t_cmd_node **head, t_cmd_node **new_node)
{
	t_cmd_node	*last;

	if (!*head)
	{
		*head = *new_node;
		(*new_node)->prev = NULL;
		(*new_node)->next = NULL;
	}
	last = get_last_node(*head);
	last->next = *new_node;
	(*new_node)->prev = last;
	(*new_node)->next = NULL;
	last->cmd_array = linked_list2array(last->cmd);
	if (!last->cmd_array)
		return ;
	last->cmd = NULL;
}

void	add_cmd(t_cmd_node **head, t_token *token)
{
	t_cmd_node	*current;

	current = *head;
	while (current->next)
		current = current->next;
	append_token(&current->cmd, token);
}
