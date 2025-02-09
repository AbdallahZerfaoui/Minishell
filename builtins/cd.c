/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:32:30 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/09 23:10:54 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO: case : cd $HOME/folder

void	cd(char *args[], t_shell **shell)
{
	// t_env	*home;
	char	*old_pwd;
	char	*destination;
	t_env	*oldpwd_node;

	old_pwd = get_pwd(shell);
	// home = find_node_by_key("HOME", shell);

	destination = ft_strdup(args[1]);
	if (args[1] && args[1][0] == TK_TILDE)
	{
		args[2] = NULL;
		destination = ft_strjoin(getenv("HOME"), args[1] + 1);
	}
	else if (args[1] && args[1][0] == TK_HYPHEN)
	{
		// args[2] = NULL;
		oldpwd_node = find_node_by_key("OLDPWD", (*shell));
		if (!oldpwd_node || !oldpwd_node->content[1])
		{
			ft_putstr_fd(STDERR_FILENO, "bash: cd: OLDPWD not set\n");
			(*shell)->exit_status = 1;
			return ;
		}
		destination = ft_strdup(find_node_by_key("OLDPWD", (*shell))->content[1]);
		// printf("%s\n", destination);
		//TODO segfault builtin tests line 328 or 333
	}
	else if (!args[1])
		destination = getenv("HOME");
	// destination = ft_strjoin_gnl("./", args[1]);
	// // printf("destination: %s\n", destination);
	// if (!args[1])
	// 	destination = getenv("HOME");
	if (chdir(destination) != 0)
	{
		handle_cd_error(shell, args);
		return ;
	}
	else if (args[1] && args[1][0] == TK_HYPHEN)
		printf("%s\n", destination);
	update_pwd(shell, old_pwd);
	// printf("PWD: %s\n", find_node_by_key("PWD", (*shell))->content[1]);
	// printf("im here\n");
	update_env_array(shell);
}
