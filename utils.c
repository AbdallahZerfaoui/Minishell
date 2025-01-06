/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 22:40:05 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/06 20:19:27 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unbalanced_quotes(const char *str)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == TK_S_QUOTE)
			single_quote++;
		else if (str[i] == TK_D_QUOTE)
			double_quote++;
		i++;
	}
	return ((single_quote % 2) || (double_quote % 2));
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
