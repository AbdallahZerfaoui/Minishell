/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:19:54 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/26 18:13:46 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_normal_word(t_parse_state *state)
{
	int			len;
	char		*sub_word;
	t_tree_node	*new_node;

	len = 0;
	while (!is_special_character(**(state->current), state->inside_d_quotes))
	{
		len++;
		*(state->current) = *(state->current) + 1;
	}
	sub_word = ft_substr(*(state->current) - len, 0, len);
	if (!sub_word)
		exit(1);
	if (ft_strcmp(sub_word, state->word) != 0)
	{
		new_node = build_word_tree(sub_word, state->shell);
		if (new_node)
			append_child(state->root, new_node);
	}
	if (*(state->current) > state->word && !state->inside_d_quotes)
		*(state->current) = *(state->current) - 1;
}
