/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:02:47 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/28 22:02:59 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_tokens_lst(t_token *tokens)
{
	int		len;
	t_token	*current;

	len = 0;
	current = tokens;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

