/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:28:25 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/19 14:30:56 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_till_n(char **result, size_t j)
{
	while (j > 0 && result[j])
	{
		j--;
		free(result[j]);
	}
	free(result);
	return (NULL);
}

void	free_if_not_in_gc(char *str)
{
	t_garbage_collector	*gc;
	t_gc_node			*current;
	size_t				i;

	if (!str)
		return ;
	i = 0;
	gc = get_gc();
	current = gc->head;
	while (current && i < gc->size)
	{
		if (current->pointer == str)
			return ;
		current = current->next;
		i++;
	}
	free(str);
}

void	free_all_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free_if_not_in_gc(split[i]);
		i++;
	}
	free_if_not_in_gc((char *)split);
}
