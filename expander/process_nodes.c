/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:31:44 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/26 18:12:17 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/***
 * This function replaces the variable in the string with the value
 * @param str the string to replace the variable in
 * @param var the variable to replace
 * @param value the value to replace the variable with
 * @return the new string with the variable replaced
 * how it works:
 * 1- find the variable in the string
 * 2- calculate the lengths of the parts before and after the variable
 * 3- allocate memory for the new string
 * 4- construct the new string
 * 5- return the new string
 */
char	*replace_var(char *str, char *var, char *value)
{
	char	*pos;
	char	*result;
	int		len_before;
	int		len_after;

	if (!str)
		return (NULL);
	if (!var)
		return (ft_strdup(str));
	if (!value)
		value = ft_strdup("");
	pos = ft_strstr(str, var);
	if (!pos)
		return (ft_strdup(str));
	len_before = pos - str;
	len_after = ft_strlen(pos + ft_strlen(var));
	result = (char *)ft_malloc(len_before + ft_strlen(value) + len_after + 1);
	if (!result)
		return (NULL);
	ft_strncpy(result, str, len_before);
	ft_strcpy(result + len_before, value);
	ft_strcpy(result + len_before + ft_strlen(value), pos + ft_strlen(var));
	return (result);
}

/***
 * This function handles the escape sequences in the string
 * example: \\ -> \ or \$ -> $
 */
static void	handle_escape_sequences(t_tree_node *root)
{
	if (root->can_expand && !root->children)
	{
		if (ft_strlen(root->value) == 2)
		{
			if (ft_strcmp(root->value, "\\\\") == 0)
				root->value = ft_strdup("\\");
			else if (ft_strcmp(root->value, "\\$") == 0)
				root->value = ft_strdup("$");
		}
	}
}

/***
 * This function handles the special variables like $? and ~
 * @param root the root node of the tree
 * @param shell the shell structure
 */
static void	handle_special_variables(t_tree_node *root, t_shell *shell)
{
	if (root->can_expand)
	{
		if (ft_strstr(root->value, "$?"))
		{
			root->value = replace_var(root->value, "$?",
					ft_itoa(shell->exit_status));
			// root->can_expand = 0;
		}
		else if (ft_strcmp(root->value, "~") == 0)
			root->value = ft_strdup(ft_getenv("HOME", shell));
	}
}

// void	process_nodes(t_tree_node *root, t_shell *shell)
// {
// 	char	*dollar_sign;

// 	if (!root)
// 		return ;
// 	dollar_sign = ft_strchr(root->value, TK_DOLLAR);
// 	if (dollar_sign && *(dollar_sign + 1) == '\0' && !root->children
// 		&& !root->next_sibling)
// 	{
// 		root->can_expand = 0;
// 	}
// 	handle_escape_sequences(root);
// 	handle_special_variables(root, shell);
// 	handle_env_variables(root, shell, dollar_sign);
// 	if (root->can_expand && root->children == NULL
// 		&& root->value[0] == TK_D_QUOTE)
// 	{
// 		root->value = ft_substr(root->value, 1, ft_strlen(root->value) - 2);
// 		if (!root->value)
// 			root->value = ft_strdup("");
// 	}
// 	process_nodes(root->children, shell);
// 	process_nodes(root->next_sibling, shell);
// }

/**
 * This function is recursive and will process the nodes of the tree
 */
void	process_nodes(t_tree_node *root, t_shell *shell)
{
	char	*dollar_sign;

	if (!root)
		return ;
	handle_escape_sequences(root);
	handle_special_variables(root, shell);
	dollar_sign = ft_strchr(root->value, TK_DOLLAR);
	while (dollar_sign)
	{
		if (dollar_sign && *(dollar_sign + 1) == '\0' && !root->children
			&& !root->next_sibling)
		{
			root->can_expand = 0;
			break ;
		}
		handle_env_variables(root, shell, dollar_sign);
		dollar_sign = ft_strchr(dollar_sign + 1, TK_DOLLAR);
	}
	if (root->can_expand && root->children == NULL
		&& root->value[0] == TK_D_QUOTE)
	{
		root->value = ft_substr(root->value, 1, ft_strlen(root->value) - 2);
		if (!root->value)
			root->value = ft_strdup("");
	}
	process_nodes(root->children, shell);
	process_nodes(root->next_sibling, shell);
}
