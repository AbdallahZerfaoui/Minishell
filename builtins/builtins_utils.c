/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:47:07 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 21:23:16 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_args(char *args[])
{
	int	len;

	len = 0;
	if (!args)
		return (len);
	while (args[len])
		len++;
	return (len);
}

/**
 * @param search for the key in the env_lst
 * @return the node if found, NULL otherwise
 */
t_env	*find_node_by_key(char *key, t_shell *shell)
{
	t_env	*current;

	current = shell->env_lst;
	while (current && current->content)
	{
		if (ft_strcmp(current->content[0], key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
