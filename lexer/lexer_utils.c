/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:02:12 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/02 17:03:49 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_expansion_chars(const char *str) // need improvement
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == TK_D_QUOTE || str[i] == TK_S_QUOTE)
		{
			count++;
			i++;
			while (str[i] && str[i] != str[i - 1])
				i++;
		}
		else if (str[i] == TK_DOLLAR || str[i] == TK_QUESTION_MARK
			|| str[i] == TK_TILDE || str[i] == TK_BACK_SLASH)
		{
			count++;
			i++;
			while (str[i] && str[i] != str[i - 1])
				i++;
		}
		else
			i++;
	}
	return (count);
}

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
	new_token->next = NULL;
}
void free_if_not_in_gc(char *str)
{
	t_garbage_collector	*gc;
	t_gc_node			*current;
	size_t				i;

	if (!str)
		return ;
	i = 0;
	gc = get_gc();
	current = gc->head;
	while (current && i < gc->size)
	{
		if (current->pointer == str)
			return ;
		current = current->next;
		i++;
	}
	free(str);
}

void	free_all_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		// free(split[i]);
		free_if_not_in_gc(split[i]);
		i++;
	}
	// free(split);
	free_if_not_in_gc((char *)split);
}
