/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:15:40 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 22:57:22 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_file(t_cmd_node **head, t_token *token)
{
	t_cmd_node	*current;

	current = *head;
	while (current->next)
		current = current->next;
	append_token(&current->files, token);
}

t_token	*move_forward_n(t_token *token, int n)
{
	int	i;

	i = 0;
	if (!token)
		return (NULL);
	while (i < n && token)
	{
		token = token->next;
		i++;
	}
	return (token);
}

int	get_words_chain_len(t_token *token)
{
	int	len;

	len = 0;
	while (token && token->type == WORD)
	{
		len++;
		token = token->next;
	}
	return (len);
}

char	**linked_list2array(t_token *tokens)
{
	t_token	*current;
	char	**array;
	int		i;

	i = 0;
	current = tokens;
	array = (char **)ft_calloc(get_words_chain_len(tokens) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	while (current)
	{
		array[i] = ft_strdup(current->value);
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
