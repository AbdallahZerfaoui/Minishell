/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:32:30 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 22:35:00 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(char *args[], t_shell **shell)
{
	char	*old_pwd;
	char	*destination;

	old_pwd = get_pwd(shell);
	destination = get_cd_destination(args, shell);
	if (!destination)
		return ;
	if (chdir(destination) != 0)
	{
		handle_cd_error(shell, args);
		return ;
	}
	else if (args[1] && args[1][0] == TK_HYPHEN)
	{
		printf("%s\n", destination);
	}
	else
		(*shell)->exit_status = 0;
	update_pwds(shell, old_pwd);
	update_env_array(shell);
}
