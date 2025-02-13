/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:52:00 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/12 21:24:04 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief This function counts the number of words in the string
 * a word is a sequence of characters separated by spaces or  <, >, <<, >>
 */
static size_t	count_words(char const *str)
{
	size_t	len;
	int		is_new_word; // change it to inside_word
	int		inside_s_quotes;
	int		inside_d_quotes;

	len = 0;
	is_new_word = 0;
	inside_s_quotes = 0;
	inside_d_quotes = 0;
	while (*str)
	{
		if (*str == TK_PIPE)
		{
			len++;
			str++;
			is_new_word = 0;
			continue ;
		}
		if (*str == TK_D_QUOTE && !inside_s_quotes)
			inside_d_quotes = !inside_d_quotes;
		if (*str == TK_S_QUOTE && !inside_d_quotes)
			inside_s_quotes = !inside_s_quotes;
		if ((*str == TK_GREATER || *str == TK_LESS)
			&& !inside_s_quotes && !inside_d_quotes)
		{
			len++;
			str += (*str == *(str + 1)) ? 1 : 0; // if the next char is the same as the current char, we skip it
			is_new_word = 0;
		}
		else if ((*str != TK_SPACE
			&& !inside_s_quotes && !inside_d_quotes)
			&& !is_new_word)
		{
			len++;
			is_new_word = 1;
		}
		else if ((*str == TK_SPACE && !inside_s_quotes && !inside_d_quotes))
			is_new_word = 0;
		str++;
	}
	return (len);
}

static size_t	get_word_len(char const *str, size_t *i)
{
	size_t	len;
	int		inside_s_quotes;
	int		inside_d_quotes;

	inside_s_quotes = 0;
	inside_d_quotes = 0;
	while (str[*i] == TK_SPACE)
		(*i)++;
	len = 0;
	if (str[*i] == TK_PIPE)
		return (1);
	else if ((str[*i + len] == TK_GREATER || str[*i + len] == TK_LESS) && str[*i + len] == str[*i + len + 1])
	{
		return (2);
	}
	else if (str[*i + len] == TK_GREATER || str[*i + len] == TK_LESS)
	{
		return (1);
	}
	while (str[*i + len])
	{
		if (str[*i + len] == TK_D_QUOTE && !inside_s_quotes)
			inside_d_quotes = !inside_d_quotes;
		if (str[*i + len] == TK_S_QUOTE && !inside_d_quotes)
			inside_s_quotes = !inside_s_quotes;
		if (!inside_s_quotes && !inside_d_quotes)
		{
			if (str[*i + len] == TK_SPACE)
				break ;
			if (str[*i + len] == TK_GREATER || str[*i + len] == TK_LESS)
				break ;
		}
		len++;
	}
	return (len);
}


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

char	**lex_split(char const *s)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s || !ft_strlen(s))
		return (NULL);
	result = (char **)ft_calloc(count_words(s) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		len = get_word_len(s, &i);
		if (len)
		{
			result[j] = ft_substr(s, i, len);
			if (!result[j])
				return (free_till_n(result, j), NULL);
			j++;
		}
		i += len;
	}
	return (result[j] = NULL, result);
}
