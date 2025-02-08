/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:23:23 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/08 15:43:39 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	char	cwd[512];
	char	*tmp;

	tmp = getcwd(cwd, sizeof(cwd));
	if (!tmp)
	{
		ft_putstr_fd(STDERR, "getcwd");
		return (NULL);
	}
	return (ft_strdup(cwd));
}

int	pwd(void)
{
	char	*cwd;
	// char	*tmp;

	cwd = get_pwd();
	if (!cwd)
		return (1);
	printf("%s\n", cwd);
	return (0);
}
