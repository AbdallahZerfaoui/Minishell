/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:22:17 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/19 13:33:38 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_separator(char c)
{
	return (c == TK_SPACE || c == TK_S_QUOTE || c == TK_D_QUOTE);
}

static char	*process_separator(const char *str, int *i)
{
	char	*sep;

	sep = ft_substr(str, *i, 1);
	(*i)++;
	return (sep);
}

/***
 * this function will return the string between the current position
 * and the next space or dollar sign or quote
 */
static char	*process_dollar(const char *str, int *i)
{
	int		start;
	int		end;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != TK_SPACE && str[*i] != TK_DOLLAR
		&& str[*i] != TK_S_QUOTE && str[*i] != TK_D_QUOTE)
		(*i)++;
	end = *i;
	return (ft_substr(str, start, end - start));
}

static char	*process_word(const char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i] && !is_separator(str[*i]) && str[*i] != TK_DOLLAR)
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

/**
 * i will create a heredoc split that splits
 * only on spaces and $ signe and quotes
 * it keeps the separators in the array
 */
char	**ft_split_heredoc(const char *str)
{
	char	**split;
	int		i;
	int		j;
	int		segments;

	i = 0;
	j = 0;
	segments = count_segments(str);
	split = (char **)ft_calloc(segments + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (str[i])
	{
		if (is_separator(str[i]))
			split[j++] = process_separator(str, &i);
		else if (str[i] == TK_DOLLAR)
			split[j++] = process_dollar(str, &i);
		else
			split[j++] = process_word(str, &i);
		j++;
	}
	split[j + 1] = NULL;
	return (split);
}
