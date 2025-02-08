/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:26:38 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/07 19:41:28 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtins(char *path, char *args[], t_shell **shell)
{
	if (ft_strstr(path, "pwd") != NULL)
		pwd();
	// else if (ft_strstr(path, "echo") != NULL)
	// 	echo();
	else if (ft_strstr(path, "cd") != NULL)
	{
		cd(args, shell);
		// print_env(shell);
	}
	// else if (ft_strstr(path, "export") != NULL)
	// 	export();
	else if (ft_strstr(path, "unset") != NULL)
		ft_unset(args, shell);
	else if (ft_strstr(path, "env") != NULL)
		print_env(*shell);
	else if (ft_strstr(path, "exit") != NULL) // strstr or strcmp??
		ft_exit(args, shell);
}
