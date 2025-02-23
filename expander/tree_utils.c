/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:35:30 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 17:35:42 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	are_empty_quotes(const char *word)
{
	if (ft_strlen(word) == 2 && (word[0] == TK_D_QUOTE || word[0] == TK_S_QUOTE)
		&& word[1] == word[0])
		return (1);
	else
		return (0);
}

int	count_quotes(char *word)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!word || *word == '\0')
		return (0);
	while (word[i])
	{
		if (word[i] == TK_D_QUOTE || word[i] == TK_S_QUOTE)
			count++;
		i++;
	}
	return (count);
}

int	count_dollars(char *word)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!word || *word == '\0')
		return (0);
	while (word[i])
	{
		if (word[i] == TK_DOLLAR)
			count++;
		i++;
	}
	return (count);
}

int	is_expansion_done(char *word) // im not sure that these are all the cases
{
	if (count_quotes(word) == 0 && count_dollars(word) == 0)
		return (1);
	else if (are_empty_quotes(word))
		return (1);
	return (0);
}
