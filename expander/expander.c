/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:04:38 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 16:54:57 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_word(char *word, t_shell *shell)
{
	char		*expanded;
	t_tree_node	*root;

	expanded = NULL;
	root = build_word_tree(word, shell);
	if (!root)
		return (NULL);
	process_nodes(root, shell, 0);
	merge_tree_nodes(root, &expanded);
	return (expanded);
}

char	*hd_expand_word_stop_word(char *word, t_shell *shell)
{
	char		*expanded;
	t_tree_node	*root;

	expanded = NULL;
	root = build_word_tree(word, shell);
	if (!root)
		return (NULL);
	process_nodes(root, shell, 1);
	merge_tree_nodes(root, &expanded);
	return (expanded);
}

t_token	*expand(t_token *tokens, t_shell **shell)
{
	t_token	*head;
	t_token	*new;

	head = NULL;
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == WORD && tokens->need_expand)
		{
			if (tokens->prev && tokens->prev->type == HEREDOC)
				new = create_token(hd_expand_word_stop_word(tokens->value,
							*shell), WORD);
			else
				new = create_token(expand_word(tokens->value, *shell), WORD);
		}
		else
			new = create_token(ft_strdup(tokens->value), tokens->type);
		if (!new)
			return (NULL);
		append_token(&head, new);
		tokens = tokens->next;
	}
	return (head);
}
