/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:52:00 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/22 20:14:08 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, char c)
{
	size_t	len;
	int		is_new_word;

	len = 0;
	is_new_word = 0;
	while (*str)
	{
		if (*str != c && !is_new_word)
		{
			is_new_word = 1;
			len++;
		}
		else if (*str == c)
			is_new_word = 0;
		str++;
	}
	return (len);
}

static size_t	get_word_len(char const *str, size_t *i, char c)
{
	size_t	len;

	while (str[*i] == c)
		(*i)++;
	len = 0;
	while (str[*i + len] && str[*i + len] != c)
		len++;
	return (len);
}

static void	*free_all(char **result, size_t j)
{
	while (j > 0)
	{
		j--;
		free(result[j]);
	}
	free(result);
	return (NULL);
}

// use ft_substr in ft_split
char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		len = get_word_len(s, &i, c);
		if (len)
		{
			result[j] = ft_substr(s, i, len);
			if (!result[j])
				return (free_all(result, j));
			j++;
		}
		i += len;
	}
	return (result[j] = NULL, result);
}
