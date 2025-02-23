/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:18:50 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 21:10:59 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote_next(char **str)
{
	char	next_char;

	next_char = *(*str + 1);
	if (next_char == TK_D_QUOTE || next_char == TK_S_QUOTE)
	{
		(*str)++;
		return (1);
	}
	return (0);
}

int	contains_slash(t_parse_state *state)
{
	char		*sub_word;
	int			len_until_slash;

	if (ft_strchr(*(state->current), TK_SLASH) != NULL)
	{
		len_until_slash = ft_strchr(*(state->current), TK_SLASH)
			- *(state->current);
		sub_word = ft_substr(*(state->current), 0, len_until_slash);
		*(state->current) = ft_strjoin(ft_getenv(sub_word + 1, state->shell),
				ft_strchr(*(state->current), TK_SLASH));
		return (1);
	}
	return (0);
}

int	handle_variable_expansion(t_parse_state *state)
{
	int			len;
	char		*sub_word;
	t_tree_node	*new_node;

	if (contains_slash(state) || is_quote_next(state->current))
		return (1);
	(*(state->current))++;
	len = len_until_special_character(*(state->current));
	sub_word = ft_substr(*(state->current) - 1, 0, len + 1);
	if (!sub_word)
		exit(1);
	if (ft_strcmp(sub_word, state->word) != 0)
	{
		new_node = build_word_tree(sub_word, state->shell);
		if (new_node)
			append_child(state->root, new_node);
	}
	return (*(state->current) += len - 1, 0);
}
