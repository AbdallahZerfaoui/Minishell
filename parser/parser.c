/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:50:45 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 22:46:10 by azerfaou         ###   ########.fr       */
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
