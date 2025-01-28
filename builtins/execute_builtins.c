/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:26:38 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/28 18:56:24 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtins(char *path)
{
	if (ft_strstr(path, "pwd") != NULL)
		pwd();
	// else if (ft_strstr(path, "echo") != NULL)
	// 	echo();
	// else if (ft_strstr(path, "cd") != NULL)
	// 	cd();
	// else if (ft_strstr(path, "export") != NULL)
	// 	export();
	// else if (ft_strstr(path, "unset") != NULL)
	// 	unset();
	// else if (ft_strstr(path, "env") != NULL)
	// 	env();
	else if (ft_strstr(path, "exit") != NULL) // strstr or strcmp??
		exit(0);
}
