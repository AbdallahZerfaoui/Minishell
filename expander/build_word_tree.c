/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_word_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:23:21 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 18:25:00 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree_node	*handle_empty_cases(char *word)
{
	if (!word || *word == '\0')
		return (NULL);
	if (are_empty_quotes(word))
		return (create_tree_node(""));
	return (NULL);
}

void	handle_escape_sequences(t_tree_node **root, char *word, t_shell *shell)
{
	t_tree_node	*new_node;

	if (ft_strlen(word) >= 2 && word[0] == TK_BACK_SLASH && (word[1] == word[0]
			|| word[1] == TK_DOLLAR))
	{
		new_node = create_tree_node(ft_substr(word, 0, 2));
		if (new_node)
			append_child(root, new_node);
		new_node = build_word_tree(word + 2, shell);
		if (new_node)
			append_child(root, new_node);
	}
}

t_tree_node	*process_word(t_parse_state *state)
{
	static int	inside_d_quotes;

	state->inside_d_quotes = inside_d_quotes;
	while (*(state->current) && **(state->current) != TK_NULL_CHAR)
	{
		if (**(state->current) == TK_D_QUOTE)
			inside_d_quotes = !inside_d_quotes;
		if (**(state->current) == TK_D_QUOTE || (**(state->current) == TK_S_QUOTE
				&& !inside_d_quotes))
		{
			*(state->current) = process_quotes(state);
			if (!*(state->current))
				return (NULL);
			else if (**(state->current) == TK_D_QUOTE)
				inside_d_quotes = !inside_d_quotes;
		}
		else if (**(state->current) == TK_DOLLAR)
		{
			if (handle_variable_expansion(state))
				continue ;
		}
		else
			handle_normal_word(state);
		*(state->current) = *(state->current) + 1;
	}
	return (*(state->root));
}


t_parse_state	*init_parse_state(t_tree_node **root, char *word,
		t_shell *shell, char **current)
{
	t_parse_state	*state;

	state = (t_parse_state *)ft_calloc(1, sizeof(t_parse_state));
	if (!state)
		exit(1);
	state->word = word;
	state->shell = shell;
	state->root = root;
	state->current = current;
	state->inside_d_quotes = 0;
	return (state);
}

/***
 * @note be careful this function is recursive
 */
t_tree_node	*build_word_tree(char *word, t_shell *shell)
{
	char			*current_char;
	t_tree_node		*root;
	t_parse_state	*state;

	root = create_tree_node(word);
	if (!root)
		exit(1);
	if (!word || *word == '\0')
		return (NULL);
	else if (are_empty_quotes(word))
		return (create_tree_node(""));
	handle_escape_sequences(&root, word, shell);
	if (is_expansion_done(word))
		return (create_tree_node(word));
	current_char = word;
	state = init_parse_state(&root, word, shell, &current_char);
	return (process_word(state));
}
