/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 22:40:05 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/17 22:16:59 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	update_env_array(t_shell **shell)
{
	if ((*shell)->env)
		(*shell)->env = NULL;
	(*shell)->env = env_lst_to_array((*shell)->env_lst);
	// print_env(*shell);
}

void	init_shell(t_shell **shell, char **env)
{
	// (*shell) = (t_shell *)ft_calloc(1, sizeof(t_shell));
	// if (!(*shell))
	// 	return ;
	(*shell)->env = env;
	(*shell)->env_lst = get_env_lst(env);
	(*shell)->exit_status = 0; //TODO: check if it should be 1
	(*shell)->hd_must_expand = 1;
}
// char	*read_and_validate_input(void)
// {
// 	char *line;
// 	char *trimmed_line;

// 	if (isatty(fileno(stdin)))
// 	{
// 		line = readline(MAGENTA "Minishell> " RESET);
// 		line = ft_strtrim(line, " \n");
// 		if (!line)
// 			return (NULL);
// 	}
// 	else
// 	{
// 		line = get_next_line(fileno(stdin));
// 		if (!line || line[0] == '\0')
// 			return (NULL);
// 		trimmed_line = ft_strtrim(line, "\n");
// 		if (!trimmed_line)
// 			return (NULL);
// 		line = trimmed_line;
// 	}

// 	if (!line)
// 		return (NULL);

// 	if (ft_strcmp(line, "exit") == 0)
// 		return (NULL);

// 	if (line[0] == '\0')
// 		return ("");

// 	if (unbalanced_quotes(line))
// 	{
// 		printf(RED "Unbalanced quotes\n" RESET);
// 		return ("");
// 	}

// 	if (line[0] != '\0')
// 		add_history(line);

// 	return (line);
// }
