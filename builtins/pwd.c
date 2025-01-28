/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:23:23 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/28 18:37:52 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(void)
{
	char	cwd[512];
	char	*tmp;

	tmp = getcwd(cwd, sizeof(cwd));
	if (!tmp)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
