/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:02:12 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/26 15:11:40 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(char *value, char *type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = ft_strdup(type);
	return (new);
}

t_token	*get_last_token(t_token *token)
{
	while (token->next)
		token = token->next;
	return (token);
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*last;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	last = get_last_token(*head);
	last->next = new_token;
	new_token->prev = last;
	new_token->next = NULL;
}
