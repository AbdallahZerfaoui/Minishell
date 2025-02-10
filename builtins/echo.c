/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:01:13 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/10 21:03:26 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *args[], t_shell **shell)
{
	int	i;
	int	j;
	int	n_flag;

	n_flag = get_n_flag(args);
	i = n_flag;
	// if (n_flag > 1)
	// 	i += 1;
	j = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag == 1)
		printf("\n");
	(*shell)->exit_status = 0;
}
