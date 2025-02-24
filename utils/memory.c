/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:28:25 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/24 13:47:31 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	free_all_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		gc_untracked_free(split[i]);
		i++;
	}
	gc_untracked_free((char *)split);
}
