/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:32:30 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/06 15:30:42 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(char *args[], t_shell **shell)
{
	// t_env	*home;
	char	*old_pwd;
	char	*destination;

	old_pwd = get_pwd();
	// home = find_node_by_key("HOME", shell);

	destination = ft_strdup(args[1]);
	if (args[1] && args[1][0] == '~')
		destination = ft_strjoin(getenv("HOME"), args[1] + 1);
	else if (!args[1])
		destination = getenv("HOME");
	// destination = ft_strjoin_gnl("./", args[1]);
	// // printf("destination: %s\n", destination);
	// if (!args[1])
	// 	destination = getenv("HOME");
	if (chdir(destination) != 0)
	{
		handle_cd_error(shell, destination);
		return ;
	}
	update_pwd(shell, old_pwd);
	// printf("PWD: %s\n", find_node_by_key("PWD", (*shell))->content[1]);
	// printf("im here\n");
	update_env_array(shell);
}
