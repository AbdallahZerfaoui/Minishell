/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:02:12 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/19 14:33:39 by azerfaou         ###   ########.fr       */
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
