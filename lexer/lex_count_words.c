/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_count_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:11:49 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/26 19:58:47 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_pipe(size_t *len, int *inside_word, char const **str)
{
	if (**str == TK_PIPE)
	{
		(*len)++;
		(*str)++;
		*inside_word = 0;
		return (1);
	}
	return (0);
}

static void	handle_redirection(size_t *len, int *inside_word, char const **str)
{
	(*len)++;
	if (*(*str + 1) == **str)
		(*str)++;
	*inside_word = 0;
}

/**
 * @brief This function counts the number of words in the string
 * a word is a sequence of characters separated by spaces or  <, >, <<, >>
 */
size_t	lex_count_words(char const *str)
{
	size_t	len;
	int		inside_word;
	int		inside_s_quotes;
	int		inside_d_quotes;

	len = 0;
	inside_word = 0;
	inside_s_quotes = 0;
	inside_d_quotes = 0;
	while (*str)
	{
		if (handle_pipe(&len, &inside_word, &str))
			continue ;
		toggle_quote_state(*str, &inside_s_quotes, &inside_d_quotes);
		if ((*str == TK_GREATER || *str == TK_LESS) && !inside_s_quotes
			&& !inside_d_quotes)
			handle_redirection(&len, &inside_word, &str);
		else if ((*str != TK_SPACE && !inside_s_quotes && !inside_d_quotes)
			&& !inside_word)
			len++;
		inside_word = !inside_word;
		str++;
	}
	return (len);
}
