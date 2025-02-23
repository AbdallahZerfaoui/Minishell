/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:18:50 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 18:19:14 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_variable_expansion(t_parse_state *state)
{
	int			len;
	int			len_until_slash;
	char		*sub_word;
	t_tree_node	*new_node;

	if (ft_strchr(*(state->current), TK_SLASH) != NULL)
	// TODO clean this hell - it is the case $HOME/Desktop
	{
		len_until_slash = ft_strchr(*(state->current), TK_SLASH)
			- *(state->current);
		sub_word = ft_substr(*(state->current), 0, len_until_slash);
		*(state->current) = ft_strjoin(ft_getenv(sub_word + 1, state->shell),
				ft_strchr(*(state->current), TK_SLASH));
		return (1);
	}
	// Check for $" or $' pattern
	if (*(*(state->current) + 1) == TK_D_QUOTE || *(*(state->current)
			+ 1) == TK_S_QUOTE)
	{
		*(state->current) = *(state->current) + 1;
			// Skip the $ and continue with quote handling
		return (1);
	}
	*(state->current) = *(state->current) + 1; // Move past $
	len = len_until_special_character(*(state->current));
	// Include $ in substring
	sub_word = ft_substr(*(state->current) - 1, 0, len + 1);
	if (!sub_word)
		exit(1);
	if (ft_strcmp(sub_word, state->word) != 0)
	{
		new_node = build_word_tree(sub_word, state->shell);
		if (new_node)
			append_child(state->root, new_node);
	}
	*(state->current) += len - 1;
	return (0);
}
