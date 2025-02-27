/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:38:35 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 17:19:05 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_cd_error(t_shell **shell, char *args[])
{
	char	*error_msg;

	if (!shell || !*shell)
		return ;
	error_msg = "bash: cd: ";
	if (args[2] != NULL)
	{
		error_msg = ft_strjoin(error_msg, "too many arguments\n");
		ft_putstr_fd(STDERR_FILENO, error_msg);
		(*shell)->exit_status = 1;
		return ;
	}
	error_msg = ft_strjoin(error_msg, args[1]);
	if (access(args[1], F_OK) == -1)
		error_msg = ft_strjoin(error_msg, ": No such file or directory\n");
	else if (access(args[1], R_OK) == -1)
		error_msg = ft_strjoin(error_msg, ": Permission denied\n");
	else
		error_msg = ft_strjoin(error_msg, ": Not a directory\n");
	ft_putstr_fd(STDERR_FILENO, error_msg);
	(*shell)->exit_status = 1;
}

// TODO check if i need to update shell at the end of the fucntion
void	update_pwds(t_shell **shell, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp;
	t_env	*pwd_node;

	pwd_node = find_node_by_key("PWD", *shell);
	new_pwd = get_pwd(shell);
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (find_node_by_key("OLDPWD", *shell))
	{
		find_node_by_key("OLDPWD", *shell)->content[1] = ft_strdup(old_pwd);
		update_env_array(shell);
	}
	else
		add_env_node(&((*shell)->env_lst), tmp);
	pwd_node->content[1] = ft_strdup(new_pwd);
}

char	*get_cd_destination(char *args[], t_shell **shell)
{
	char	*destination;
	t_env	*oldpwd_node;

	if (!args[1])
		return (ft_getenv("HOME", *shell));
	if (args[1][0] == TK_TILDE)
	{
		args[2] = NULL;
		destination = ft_strjoin(ft_getenv("HOME", *shell), args[1] + 1);
		return (destination);
	}
	if (args[1][0] == TK_HYPHEN)
	{
		oldpwd_node = find_node_by_key("OLDPWD", (*shell));
		if (!oldpwd_node || !oldpwd_node->content[1])
		{
			ft_putstr_fd(STDERR_FILENO, "bash: cd: OLDPWD not set\n");
			(*shell)->exit_status = 1;
			return (NULL);
		}
		destination = ft_strdup(oldpwd_node->content[1]);
		return (destination);
	}
	return (ft_strdup(args[1]));
}
