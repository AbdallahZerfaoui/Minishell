/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_validate_input.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:29:43 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/23 22:26:34 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_waiting_for_input = 1;

// TODO improve this exit shit
char	*read_and_validate_input(int is_interactive)
{
	char	*line;
	char	*trimmed_line;

	g_waiting_for_input = 1;
	if (is_interactive)
	{
		line = readline(MAGENTA "⚡️ root@minihell ☠️ ~> " RESET);
		line = ft_strtrim(line, " \n");
		if (!line)
			return (NULL);
	}
	else
	{
		line = get_next_line(fileno(stdin));
		if (!line)
			return ("exit");
		trimmed_line = ft_strtrim(line, "\n");
		if (!trimmed_line)
			return ("exit");
		line = trimmed_line;
	}
	if (line[0] != '\0')
		g_waiting_for_input = 0;
	if (!line)
		return (NULL);
	if (unbalanced_quotes(line))
	{
		printf(RED "Unbalanced quotes\n" RESET);
		return ("");
	}
	if (is_interactive)
		add_history(line);
	return (line);
}
