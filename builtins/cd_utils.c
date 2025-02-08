/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:38:35 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/08 23:36:00 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_cd_error(t_shell **shell, char *args[])
{
	char	*error_msg;

	if (!shell || !*shell)
		return ;

	error_msg = "bash: cd: ";
	ft_putstr_fd(STDERR_FILENO, error_msg);
	if (args[2] != NULL)
	{
		error_msg = "too many arguments\n";
		ft_putstr_fd(STDERR_FILENO, error_msg);
		(*shell)->exit_status = 1;
		return ;
	}
	ft_putstr_fd(STDERR_FILENO, args[1]);
	if (access(args[1], F_OK) == -1)
		error_msg = ": No such file or directory\n";
	else if (access(args[1], R_OK) == -1)
		error_msg = ": Permission denied\n";
	else
		error_msg = ": Not a directory\n";

	ft_putstr_fd(STDERR_FILENO, error_msg);
	(*shell)->exit_status = 1;
}

void	update_pwd(t_shell **shell, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp;
	t_env	*pwd_node;

	pwd_node = find_node_by_key("PWD", *shell);
	new_pwd = get_pwd();
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (find_node_by_key("OLDPWD", *shell))
	{
		find_node_by_key("OLDPWD", *shell)->content[1] = ft_strdup(old_pwd);
		update_env_array(shell);
	}
	else
		add_env_node(&((*shell)->env_lst), tmp);
	// add_env_node(&((*shell)->env_lst), tmp);
	// printf("new_pwd 2 : %s\n", new_pwd);
	pwd_node->content[1] = ft_strdup(new_pwd);
	// tmp = ft_strjoin("PWD=", new_pwd);
	// add_env_node(&shell->env_lst, tmp);
	// free(new_pwd);
	// print_env(shell);
}

