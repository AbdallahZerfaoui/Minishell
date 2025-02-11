/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:15:13 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/11 20:53:51 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*last_node(t_env *env_lst)
{
	t_env	*last;

	last = env_lst;
	while (last->next)
		last = last->next;
	return (last);
}

// int	is_valid_key(char *key)
// {
// 	int	i;

// 	i = 0;
// 	while (key[i])
// 	{
// 		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
/**
 * @brief Add a new node to the env_lst
 * step 1: allocate memory for the new node
 * step 2: split the entry by '='
 * step 3: if the env_lst is empty, assign the new node to the env_lst
 */
void	add_env_node(t_env **env_lst, char *entry)
{
	t_env	*new;
	t_env	*last;

	new = (t_env *)ft_calloc(1, sizeof(struct s_env));
	if (!new)
		return ;
	//TODO be careful with the split, some lines contain several '='
	new->content = ft_split(entry, '='); 
	if (!new->content)
	{
		free(new);
		return ;
	}
	if (!(*env_lst))
	{
		(*env_lst) = new;
		return ;
	}
	last = last_node(*env_lst);
	last->next = new;
	new->prev = last;
}

/**
 * @brief Get the value of an environment variable
 * it uses the linked list to get the value of the key
 * @note This function is used by the expander
 */
char	*ft_getenv(char *key, t_shell *shell)
{
	t_env	*current;

	if (!key || !shell)
		return (NULL);
	current = shell->env_lst;
	while (current)
	{
		if (ft_strcmp(current->content[0], key) == 0)
			return (current->content[1]);
		current = current->next;
	}
	return (NULL);
}
