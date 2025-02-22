/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:50:45 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/22 17:36:24 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*detach_token(t_token *target, int size)
{
	t_token	*previous;
	t_token	*current_updated;

	if (!target || size < 0)
		return (NULL);
	previous = target->prev;
	current_updated = move_forward_n(target, size);
	if (previous)
	{
		previous->next = current_updated;
	}
	if (current_updated)
	{
		current_updated->prev->next = NULL;
		current_updated->prev = previous;
	}
	target->prev = NULL;
	return (current_updated);
}

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

void	finalize_cmds_lst(t_cmd_node **head)
{
	t_cmd_node	*last;

	last = get_last_node(*head);
	last->cmd_array = linked_list2array(last->cmd);
	if (!last->cmd_array)
		return ;
	last->cmd = NULL;
}

t_cmd_node	*parse(t_token *tokens, t_shell **shell)
{
	t_cmd_node	*head;
	t_token		*current_token;

	head = create_cmd_node();
	if (!head || !tokens)
		return (NULL);
	current_token = tokens;
	while (current_token)
	{
		if (current_token->type == PIPE)
		{
			if (!process_pipe_token(&head, &current_token))
				return (NULL);
		}
		else if (current_token->type == WORD)
			process_word_token(&head, &current_token);
		else if (is_redirection_token(current_token))
			process_redirection_token(&head, &current_token);
		else
		{
			(*shell)->exit_status = MISUSE_ERROR;
			break ;
		}
	}
	return (finalize_cmds_lst(&head), head);
}
