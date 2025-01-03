/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:31:44 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/03 21:54:24 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_nodes(t_tree_node *root)
{
	char	*keyword;
	// char	*old_value;

	if (!root)
		return ;
	if (root->can_expand && root->children == NULL
		&& root->value[0] == TK_DOLLAR)
	{
		keyword = root->value + 1;
		// old_value = root->value;
		root->value = ft_strdup(getenv(keyword));
		if (!root->value)
			root->value = ft_strdup("");
		// free(old_value);
	}
	else if (root->can_expand && root->children == NULL
		&& root->value[0] == TK_D_QUOTE)
	{
		root->value = ft_substr(root->value, 1, ft_strlen(root->value) - 2);
		if (!root->value)
			root->value = ft_strdup("");
	}
	process_nodes(root->children);
	process_nodes(root->next_sibling);
}
