/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_validate_input.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:29:43 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 22:02:34 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_waiting_for_input = 1;

// TODO improve this exit shit
static char	*read_input(int is_interactive)
{
	char	*line;
	char	*trimmed_line;

	g_waiting_for_input = 1;
	if (is_interactive)
	{
		line = readline(MAGENTA "⚡️ root@minihell ☠️ ~> " RESET);
		if (!line)
			return (NULL);
		trimmed_line = ft_strtrim(line, " \n");
		free(line);
		if (!trimmed_line)
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
	}
	return (trimmed_line);
}

char	*read_and_validate_input(int is_interactive)
{
	char	*line;

	line = read_input(is_interactive);
	if (line && line[0] != TK_NULL_CHAR)
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
