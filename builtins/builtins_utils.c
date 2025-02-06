/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:47:07 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/06 14:15:55 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

/**
 * @note this function has a problem it blocks the code
 */
t_env	*find_node_by_key(char *key, t_shell *shell)
{
	t_env	*current;

	current = shell->env_lst;
	// if (!current || !current->content)
	// 	printf("env_lst is empty\n");
	while (current && current->content)
	{
		if (ft_strcmp(current->content[0], key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

