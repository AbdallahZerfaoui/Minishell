/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:30:16 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 23:00:49 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_d_quotes(t_parse_state *state, char *sub_word)
{
	t_tree_node	*new_node;

	if (sub_word && *sub_word != TK_NULL_CHAR
		&& ft_strcmp(sub_word, state->word) != 0
		&& **(state->current) == TK_D_QUOTE)
	{
		new_node = build_word_tree(sub_word, state->shell);
		if (new_node)
		{
			append_child(state->root, new_node);
		}
	}
}

static void	process_s_quotes_outside(t_parse_state *state, char *sub_word)
{
	t_tree_node	*new_node;

	if (**(state->current) == TK_S_QUOTE && !state->inside_d_quotes)
	{
		new_node = create_tree_node(sub_word);
		if (new_node)
		{
			new_node->can_expand = 0;
			append_child(state->root, new_node);
		}
	}
}

static void	process_s_quotes_inside(t_parse_state *state, char *sub_word)
{
	t_tree_node	*new_node;

	if (**(state->current) == TK_S_QUOTE && state->inside_d_quotes)
	{
		sub_word = ft_substr(*(state->current), 0,
				ft_strlen(*(state->current)));
		new_node = create_tree_node(sub_word);
		if (new_node)
		{
			append_child(state->root, new_node);
		}
	}
}

// TODO change the name of the variable end_last_part
char	*process_quotes(t_parse_state *state)
{
	int		len;
	char	*sub_word;
	char	*end_last_part;

	end_last_part = ft_strchr(*(state->current) + 1, **(state->current));
	if (!end_last_part)
		return (NULL);
	len = end_last_part - *(state->current) - 1;
	sub_word = ft_substr(*(state->current) + 1, 0, len);
	process_d_quotes(state, sub_word);
	process_s_quotes_outside(state, sub_word);
	process_s_quotes_inside(state, sub_word);
	*(state->current) = end_last_part;
	return (end_last_part);
}
