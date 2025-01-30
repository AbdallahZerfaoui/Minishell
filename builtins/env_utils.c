/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:15:13 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/30 11:33:14 by azerfaou         ###   ########.fr       */
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

void	add_env_node(t_env **env_lst, char *entry)
{
	t_env	*new;
	t_env	*last;

	new = (t_env *)ft_calloc(1, sizeof(struct s_env));
	if (!new)
		return ;
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
