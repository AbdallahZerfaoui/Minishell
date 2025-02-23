/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_word_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:23:21 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 17:03:09 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree_node	*create_tree_node(const char *value)
{
	t_tree_node	*new;

	new = (t_tree_node *)ft_calloc(1, sizeof(t_tree_node));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->can_expand = 1;
	new->parent = NULL;
	new->children = NULL;
	new->next_sibling = NULL;
	return (new);
}

t_tree_node	*get_last_child(t_tree_node *node)
{
	t_tree_node	*last;

	if (!node || !node->children)
		return (NULL);
	last = node->children;
	while (last && last->next_sibling)
		last = last->next_sibling;
	return (last);
}

void	append_child(t_tree_node **head, t_tree_node *new_node)
{
	t_tree_node	*last;

	if (!*head)
	{
		*head = new_node;
		new_node->parent = NULL;
		return ;
	}
	last = get_last_child(*head);
	if (!last)
	{
		(*head)->children = new_node;
		new_node->parent = *head;
		return ;
	}
	last->next_sibling = new_node;
	new_node->next_sibling = NULL;
	new_node->parent = last->parent;
}

int	are_empty_quotes(const char *word)
{
	if (ft_strlen(word) == 2 && (word[0] == TK_D_QUOTE || word[0] == TK_S_QUOTE)
		&& word[1] == word[0])
		return (1);
	else
		return (0);
}

int	count_quotes(char *word)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!word || *word == '\0')
		return (0);
	while (word[i])
	{
		if (word[i] == TK_D_QUOTE || word[i] == TK_S_QUOTE)
			count++;
		i++;
	}
	return (count);
}

int	count_dollars(char *word)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!word || *word == '\0')
		return (0);
	while (word[i])
	{
		if (word[i] == TK_DOLLAR)
			count++;
		i++;
	}
	return (count);
}

int	is_expansion_done(char *word) // im not sure that these are all the cases
{
	if (count_quotes(word) == 0 && count_dollars(word) == 0)
		return (1);
	else if (are_empty_quotes(word))
		return (1);
	return (0);
}

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

int	is_special_character(char c, int in_dquotes)
{
	return (c == TK_NULL_CHAR || c == TK_D_QUOTE || (!in_dquotes
			&& c == TK_S_QUOTE));
}

int	len_until_special_character(char *str)
{
	int	len;

	len = 0;
	while (str[len] != TK_DOLLAR && str[len] != TK_SPACE
		&& str[len] != TK_D_QUOTE && str[len] != TK_S_QUOTE
		&& str[len] != TK_NULL_CHAR)
		len++;
	return (len);
}
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

void	process_d_quotes(t_parse_state *state, char *sub_word)
{
	t_tree_node	*new_node;

	if (sub_word && *sub_word != '\0' && ft_strcmp(sub_word, state->word) != 0
		&& **(state->current) == TK_D_QUOTE)
	{
		new_node = build_word_tree(sub_word, state->shell);
		if (new_node)
		{
			append_child(state->root, new_node);
		}
	}
}

void	process_s_quotes_outside(t_parse_state *state, char *sub_word)
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

void	process_s_quotes_inside(t_parse_state *state, char *sub_word)
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

char	*process_quotes(t_parse_state *state)
{
	int		len;
	char	*sub_word;

	char *end_last_part; // TODO change the name
	end_last_part = ft_strchr(*(state->current) + 1, **(state->current));
	if (!end_last_part)
		return (NULL);
	len = end_last_part - *(state->current) - 1; // we remove the quotes
	sub_word = ft_substr(*(state->current) + 1, 0, len);
	process_d_quotes(state, sub_word);
	process_s_quotes_outside(state, sub_word);
	process_s_quotes_inside(state, sub_word);
	*(state->current) = end_last_part;
	return (end_last_part);
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
		else if (**(state->current) == TK_DOLLAR) // $ case - add !inside_s_quotes
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
