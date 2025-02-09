/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:23:23 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/09 23:02:40 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(t_shell **shell)
{
	char	cwd[512];
	char	*tmp;

	tmp = getcwd(cwd, sizeof(cwd));
	if (!tmp)
	{
		ft_putstr_fd(STDERR_FILENO, "getcwd");
		(*shell)->exit_status = 1;
		return (NULL);
	}
	return (ft_strdup(cwd));
}

int	pwd(t_shell **shell)
{
	char	*cwd;
	// char	*tmp;

	cwd = get_pwd(shell);
	if (!cwd)
		return (1);
	printf("%s\n", cwd);
	(*shell)->exit_status = 0;
	return (0);
}
