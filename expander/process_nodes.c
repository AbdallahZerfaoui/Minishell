/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:31:44 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/04 20:06:58 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *replace_var(char *str, char *var, char *value) // forbidden function
{
    char *pos;
    char *result;
    int len_before;
    int len_after;
	
	if (!str)
		return NULL;
	if (!var || !value)
		return ft_strdup(str);
    // Find the position of the variable in the string
    pos = strstr(str, var);
    if (!pos)
        return ft_strdup(str); // Variable not found, return a copy of the original string

    // Calculate the lengths of the parts before and after the variable
    len_before = pos - str; // Length of the part before the variable
    len_after = ft_strlen(pos + ft_strlen(var)); // Length of the part after the variable

    // Allocate memory for the new string
    result = (char *)ft_malloc(len_before + ft_strlen(value) + len_after + 1);
    if (!result)
        return NULL; // Return NULL if memory allocation fails

    // Construct the new string
    ft_strncpy(result, str, len_before); // Copy the part before the variable
    strcpy(result + len_before, value); // Insert the replacement value
    strcpy(result + len_before + ft_strlen(value), pos + ft_strlen(var)); // Copy the part after the variable

    return result;
}

void	process_nodes(t_tree_node *root)
{
	char	*keyword;
	char	*elem_to_replace;
	char	*tmp_char;
	char	*dollar_sign;
	int		len;
	// int		is_skipped;
	// char	*old_value;

	if (!root)
		return ;
	keyword = NULL;
	// is_skipped = 0;
	// printf("root = %s\n", root->value);
	dollar_sign = ft_strchr(root->value, TK_DOLLAR);
	if (root->can_expand && !root->children
		&& ft_strlen(root->value) == 2 && ft_strcmp(root->value, "\\\\") == 0)
	{
		root->value = ft_strdup("\\");
	}
	if (root->can_expand && !root->children
		&& ft_strlen(root->value) == 2 && ft_strcmp(root->value, "\\$") == 0)
	{
		root->value = ft_strdup("$");
	}
	else if (root->can_expand && !root->children
		&& dollar_sign != NULL)
	{
		len = 0;
		if (root->value[1] == '\0')
		{
			root->value = ft_strdup("");
		}
		// keyword = root->value + 1;
		tmp_char = dollar_sign;
		while (tmp_char != NULL && *tmp_char != '\0'
			&& *tmp_char != TK_D_QUOTE && *tmp_char != TK_S_QUOTE)
		{
			len++;
			tmp_char++;
		}
		// printf("len = %d\n", len);
		// printf("root->value = %s\n", root->value);
		elem_to_replace = ft_substr(dollar_sign, 0, len);
		// printf("elem_to_replace = %s\n", elem_to_replace);
		if (elem_to_replace)
			keyword = elem_to_replace + 1;
		// printf("keyword = %s\n", keyword);
		// old_value = root->value;
		root->value = replace_var(root->value, elem_to_replace, getenv(keyword));
		if (!root->value)
			root->value = ft_strdup("");
		// printf("im here\n");
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
