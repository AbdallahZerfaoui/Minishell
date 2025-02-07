/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:37:49 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/07 17:28:33 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_args(char **args)
{
	int	len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}

int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char *args[], t_shell *shell)
{
	int	exit_code;

	(void)shell;
	exit_code = 0;
	// if (args[2] != NULL)
	// 	exit_code = 1;
	// printf("exit args = %s\n", shell->cmds->cmd->value);
	if (args[1] && is_only_digits(args[1]) == 0)
		exit_code = 255;
	else if (len_args(args) > 2)
		exit_code = 1;
	else if (args[1] != NULL)
		exit_code = ft_atoi(args[1]);
	// printf("exit\n");
	main_cleanup();
	exit(exit_code);
}
