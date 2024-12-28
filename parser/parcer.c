/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:50:45 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/28 20:36:40 by azerfaou         ###   ########.fr       */
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

t_cmd_node	*parse(t_token *tokens)
{
	t_cmd_node	*head;
	t_cmd_node	*new_node;
	// t_token		*next_token;
	t_token		*current_token;
	t_token		*detached_token;
	int			words_chain_len;

	head = create_cmd_node();
	if (!head || !tokens)
		return (NULL);
	check_tokens(tokens);
	current_token = tokens;
	while (current_token)
	{
		if (current_token->type == PIPE)
		{
			new_node = create_cmd_node();
			if (!new_node)
				return (NULL);
			append_cmd_node(&head, &new_node);
			// next_token = current_token->next;
			current_token = current_token->next;
		}
		else if (current_token->type == WORD)
		{
			words_chain_len = get_words_chain_len(current_token);
			detached_token = current_token;
			current_token = detach_token(detached_token, words_chain_len);
			add_cmd(&head, detached_token);
		}
		else if (current_token->type == INFILE
			|| current_token->type == OUTFILE)
		{
			detached_token = current_token;
			current_token = detach_token(detached_token, 2);
			add_file(&head, detached_token);
		}
		else
		{
			perror("Invalid token type");
			exit(1);
		}
	}
	t_cmd_node	*last = get_last_node(head);
	last->cmd_array = linked_list2array(last->cmd);
	if (!last->cmd_array)
		return (NULL);
	free_tokens(last->cmd);
	last->cmd = NULL;
	return (head);
}


// int main()
// {
// 	int		i = 0;
// 	char *line = "cd | ls -al | wc -l> test.txt";
// 	//| grep \"root\" | awk '{print $1, $2, $11}' | sort -u | tee processes.log > summary.log";
// 	// char	*line = "ps aux | grep \"root\" | awk '{print $1, $2, $11}' | sort -u | tee processes.log > summary.log";
// 	// char	*line = "grep \"error\" < logs.txt | cut -d " " -f 2 > error_messages.txt";	 //problematic
// 	// printf("line = %s\n", line);
// 	t_token *tokens = lexer(line);
// 	t_cmd_node *cmds = parse(tokens);
// 	t_cmd_node *tmp = cmds;
// 	while (tmp)
// 	{
// 		// while(tmp->cmd)
// 		// {
// 		// 	printf("%s*", tmp->cmd->value);
// 		// 	tmp->cmd = tmp->cmd->next;
// 		// }
// 		// printf("\n");
// 		if (tmp->cmd_array)
// 		{
// 			i = 0;
// 			while (tmp->cmd_array[i])
// 			{
// 				printf("%s#", tmp->cmd_array[i]);
// 				i++;
// 			}
// 			printf("\n");
// 		}
// 		if (!tmp->files)
// 			printf("NULL\n");
// 		while(tmp->files)
// 		{
// 			printf("outfile = %s ", tmp->files->value);
// 			tmp->files = tmp->files->next;
// 		}
// 		printf("\n");
// 		// printf("len = %d\n", len_tokens_lst(tmp->cmd));
// 		tmp = tmp->next;
// 	}
// 	// free_tokens(tokens);
// 	free_cmds(cmds);
// }
