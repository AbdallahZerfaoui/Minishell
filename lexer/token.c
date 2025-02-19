/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:24:13 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/19 14:24:52 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/***
 * @brief This function creates a token
 * if the flag_expansion is -1, it will count the expansion chars
 * if the flag_expansion is 1 or more, it will set the need_expand to 1
 * if the flag_expansion is 0, it will set the need_expand to 0
 */
t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new;

	if (!value)
		return (NULL);
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->need_expand = count_expansion_chars(value);
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
}
