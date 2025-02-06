/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:38:35 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/06 14:16:06 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_cd_error(t_shell *shell, char *dest)
{
	printf("cd: %s: No such file or directory\n", dest);
	shell->exit_status = 1;
}

void	update_pwd(t_shell **shell, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp;
	t_env	*pwd_node;

	pwd_node = find_node_by_key("PWD", *shell);
	new_pwd = get_pwd();
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	add_env_node(&((*shell)->env_lst), tmp);
	// printf("new_pwd 2 : %s\n", new_pwd);
	pwd_node->content[1] = ft_strdup(new_pwd);
	// tmp = ft_strjoin("PWD=", new_pwd);
	// add_env_node(&shell->env_lst, tmp);
	// free(new_pwd);
	// print_env(shell);
}

