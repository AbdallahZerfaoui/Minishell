/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:52:00 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/26 16:46:15 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_words(char const *str)
{
	size_t	len;
	int		is_new_word;
	int		inside_s_quotes;
	int		inside_d_quotes;

	len = 0;
	is_new_word = 0;
	inside_s_quotes = 0;
	inside_d_quotes = 0;
	while (*str)
	{
		if (*str == TK_D_QUOTE)
			inside_d_quotes = !inside_d_quotes;
		if (*str == TK_S_QUOTE)
			inside_s_quotes = !inside_s_quotes;
		if (*str != TK_SPACE
			&& *str != TK_D_QUOTE
			&& *str != TK_S_QUOTE
			&& !is_new_word)
		{
			is_new_word = 1;
			len++;
		}
		else if (*str == TK_SPACE && !inside_s_quotes && !inside_d_quotes)
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
	while (str[*i + len]
		&& (str[*i + len] != TK_SPACE || inside_s_quotes || inside_d_quotes))
	{
		if (str[*i + len] == TK_D_QUOTE)
			inside_d_quotes = !inside_d_quotes;
		if (str[*i + len] == TK_S_QUOTE)
			inside_s_quotes = !inside_s_quotes;
		len++;
	}
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

char	**lex_split(char const *s)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_words(s) + 1));
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
				return (free_all(result, j));
			j++;
		}
		i += len;
	}
	return (result[j] = NULL, result);
}

// int main(void)
// {
// 	char	**split;
// 	// char	*str = "Hello world \"hello world\" 'hello world'";
// 	// char *str = "ls -la | grep \"hello .txt\" | sort > output.txt";
// 	char *str = "ls -la | grep \".txt\" | sort | wc -l > output.txt";

// 	int len = count_words(str);
// 	split = lex_split(str);
// 	printf("len = %d\n", len);
// 	for (int i = 0; split[i]; i++)
// 		printf("%s\n", split[i]);
// 	return (0);
// }
