/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tree_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:51:50 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 21:29:58 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	merge_tree_nodes(t_tree_node *root, char **expanded_word)
{
	if (!root)
		return ;
	while (root)
	{
		if (!root->children)
		{
			*expanded_word = ft_strjoin_gnl(*expanded_word, root->value);
			if (root->next_sibling)
				root = root->next_sibling;
			else if (root->parent && root->parent->next_sibling)
				root = root->parent->next_sibling;
			else
				root = NULL;
		}
		else
			root = root->children;
	}
}
