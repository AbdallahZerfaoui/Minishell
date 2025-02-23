/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 22:58:11 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 22:58:57 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_pipe_token(t_cmd_node **head, t_token **current_token)
{
	t_cmd_node	*new_node;

	new_node = create_cmd_node();
	if (!new_node)
		return (0);
	append_cmd_node(head, &new_node);
	*current_token = (*current_token)->next;
	return (1);
}

void	process_word_token(t_cmd_node **head, t_token **current_token)
{
	t_token		*detached_token;
	int			words_chain_len;

	words_chain_len = get_words_chain_len(*current_token);
	detached_token = *current_token;
	*current_token = detach_token(detached_token, words_chain_len);
	add_cmd(head, detached_token);
}

void	process_redirection_token(t_cmd_node **head, t_token **current_token)
{
	t_token		*detached_token;

	detached_token = *current_token;
	*current_token = detach_token(detached_token, 2);
	add_file(head, detached_token);
}

int	is_redirection_token(t_token *token)
{
	return (token->type == INFILE
		|| token->type == OUTFILE
		|| token->type == APPEND
		|| token->type == HEREDOC);
}
