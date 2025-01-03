/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tree_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:51:50 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/03 21:57:51 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	merge_tree_nodes(t_tree_node *root, char **expanded_word)
{

	if (!root)
		return ;
	while (root)
	{
		// printf("root = *%s*\n", root->value);
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
	// merge_tree_nodes(root->children, expanded_word);
	// merge_tree_nodes(root->next_sibling, expanded_word);

}
