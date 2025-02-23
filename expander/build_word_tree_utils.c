/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_word_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:28:01 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 17:28:33 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_character(char c, int in_dquotes)
{
	return (c == TK_NULL_CHAR || c == TK_D_QUOTE || (!in_dquotes
			&& c == TK_S_QUOTE));
}

int	len_until_special_character(char *str)
{
	int	len;

	len = 0;
	while (str[len] != TK_DOLLAR && str[len] != TK_SPACE
		&& str[len] != TK_D_QUOTE && str[len] != TK_S_QUOTE
		&& str[len] != TK_NULL_CHAR)
		len++;
	return (len);
}
