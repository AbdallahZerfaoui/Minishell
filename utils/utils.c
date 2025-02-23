/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 22:40:05 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 23:15:12 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/***
 * @brief This function checks if the string has unbalanced quotes.
 * instead of counting the quotes, we use two flags
 * to check if we are inside a quote
 * @note this way we eliminate the quotes inside qotes problem
 */
int	unbalanced_quotes(const char *str)
{
	int	is_single_quote;
	int	is_double_quote;
	int	i;

	is_single_quote = 0;
	is_double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == TK_S_QUOTE && !is_double_quote)
			is_single_quote = !is_single_quote;
		else if (str[i] == TK_D_QUOTE && !is_single_quote)
			is_double_quote = !is_double_quote;
		i++;
	}
	return (is_single_quote || is_double_quote);
}

/***
 * @brief This function updates the env array
 * @note this function is called after each change in the env_lst
 */
//TODO are you sure about the if condition?
void	update_env_array(t_shell **shell)
{
	if ((*shell)->env)
		(*shell)->env = NULL;
	(*shell)->env = env_lst_to_array((*shell)->env_lst);
}

//TODO: check if the exit status should be 1 or 0
void	init_shell(t_shell **shell, char **env)
{
	(*shell)->env = env;
	(*shell)->env_lst = get_env_lst(env);
	(*shell)->exit_status = 0;
	(*shell)->hd_must_expand = 1;
}
