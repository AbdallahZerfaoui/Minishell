/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:34:40 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 17:34:56 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree_node	*create_tree_node(const char *value)
{
	t_tree_node	*new;

	new = (t_tree_node *)ft_calloc(1, sizeof(t_tree_node));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->can_expand = 1;
	new->parent = NULL;
	new->children = NULL;
	new->next_sibling = NULL;
	return (new);
}

t_tree_node	*get_last_child(t_tree_node *node)
{
	t_tree_node	*last;

	if (!node || !node->children)
		return (NULL);
	last = node->children;
	while (last && last->next_sibling)
		last = last->next_sibling;
	return (last);
}

void	append_child(t_tree_node **head, t_tree_node *new_node)
{
	t_tree_node	*last;

	if (!*head)
	{
		*head = new_node;
		new_node->parent = NULL;
		return ;
	}
	last = get_last_child(*head);
	if (!last)
	{
		(*head)->children = new_node;
		new_node->parent = *head;
		return ;
	}
	last->next_sibling = new_node;
	new_node->next_sibling = NULL;
	new_node->parent = last->parent;
}
