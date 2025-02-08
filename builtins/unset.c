/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:12:53 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/08 15:48:19 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (ft_isalpha(key[i]) == 0 && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	delete_node_by_key(t_shell **shell, char *key)
{
	t_env	*current;
	t_env	*prev;
	t_env	*next;

	current = (*shell)->env_lst;
	(*shell)->exit_status = 1;
	while (current)
	{
		prev = current->prev;
		next = current->next;
		if (ft_strcmp(current->content[0], key) == 0)
		{
			if (prev)
				prev->next = next;
			if (next)
				next->prev = prev;
			if (current == (*shell)->env_lst)
				(*shell)->env_lst = next;
			(*shell)->exit_status = 0;
			update_env_array(shell);
			break ;
		}
		current = next;
	}
}

void	ft_unset(char *args[], t_shell **shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			ft_putstr_fd(STDERR, "minishell: unset: not a valid identifier\n");
			(*shell)->exit_status = 1;
			i++;
			continue;
		}
		else
			delete_node_by_key(shell, args[i]);
		i++;
	}
}
