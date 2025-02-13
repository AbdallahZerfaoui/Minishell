/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:07:52 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/13 23:07:58 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// /**
//  * this function removes the quotes from a string
//  * and returns 1 if the string was modified
//  * and 0 if it wasn't
//  */

static int	count_segments(const char *str)
{
	int		i;
	int		segments;

	i = 0;
	segments = 0;
	while (str[i])
	{
		if (str[i] == TK_SPACE || str[i] == TK_DOLLAR
			|| str[i] == TK_S_QUOTE || str[i] == TK_D_QUOTE)
			segments++;
		i++;
	}
	return (segments);
}

/**
 * i will create a heredoc split that splits only on spaces and $ signe and quotes
 * it keeps the separators in the array
 */
static char	**ft_split_heredoc(const char *str)
{
	char	**split;
	int		i;
	int		j;
	int		start;
	int		end;
	int		segments;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	segments = count_segments(str);
	split = (char **)ft_calloc(segments + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (str[i])
	{
		if (str[i] == TK_SPACE
			|| str[i] == TK_S_QUOTE || str[i] == TK_D_QUOTE)
		{
			split[j] = ft_substr(str, i, 1);
			i++;
		}
		else if (str[i] == TK_DOLLAR)
		{
			start = i;
			i++;
			while (str[i] && str[i] != TK_SPACE && str[i] != TK_DOLLAR
				&& str[i] != TK_S_QUOTE && str[i] != TK_D_QUOTE)
				i++;
			end = i;
			split[j] = ft_substr(str, start, end - start);
		}
		j++;
	}
	split[j + 1] = NULL;
	return (split);
}

char	*hd_expand_word(char *word, t_shell *shell)
{
	char	**split;
	char	*expanded;

	if (ft_strchr(word, TK_DOLLAR) == NULL)
		return (word);
	expanded = ft_strdup("");
	split = ft_split_heredoc(word);
	while (*split)
	{
		if (ft_strchr(*split, '$') != NULL)
			expanded = ft_strjoin(expanded, expand_word(*split, shell));
		else
			expanded = ft_strjoin(expanded, *split);
		split++;
	}
	return (expanded);
}

int	set_heredoc_expansion_flag(t_token *tokens)
{
	t_token	*current;
	int		need_expand;

	need_expand = 1;
	current = tokens;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (current->next && current->next->type == WORD)
			{
				need_expand
					= (count_quotes(current->next->value) == 0);
				break ;
			}
		}
		current = current->next;
	}
	return (need_expand);
}
