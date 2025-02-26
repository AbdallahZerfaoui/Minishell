/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:04:26 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/26 18:10:00 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*extract_keyword(char *dollar_sign, int *len)
{
	char	*tmp_char;
	char	*keyword;

	*len = 0;
	tmp_char = dollar_sign;
	while (tmp_char != NULL && *tmp_char != TK_NULL_CHAR
		&& *tmp_char != TK_D_QUOTE
		&& *tmp_char != TK_S_QUOTE
		&& *tmp_char != TK_SPACE)
	{
		(*len)++;
		tmp_char++;
	}
	keyword = ft_substr(dollar_sign, 0, *len);
	if (keyword)
		keyword++;
	return (keyword);
}

void	handle_env_variables(t_tree_node *root, t_shell *shell,
		char *dollar_sign)
{
	int		len;
	char	*keyword;
	char	*elem_to_replace;

	keyword = NULL;
	if (root->can_expand && !root->children && dollar_sign != NULL)
	{
		len = 0;
		if (ft_strlen(root->value) == 1)
		{
			root->can_expand = 0;
			dollar_sign = NULL;
		}
		keyword = extract_keyword(dollar_sign, &len);
		elem_to_replace = ft_substr(dollar_sign, 0, len);
		root->value = replace_var(root->value, elem_to_replace,
				ft_getenv(keyword, shell));
		if (!root->value)
			root->value = ft_strdup("");
	}
}
