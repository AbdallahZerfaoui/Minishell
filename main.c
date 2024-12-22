/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:17:53 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/22 19:13:21 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop_shell(void)
{
	char	*line;

	while (1)
	{
		line = readline(RED"minishell> "RESET);
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		if (line[0] != '\0')
			add_history(line);
		free(line);
	}
}

int	main(void)
{
	loop_shell();
	return (0);
}

