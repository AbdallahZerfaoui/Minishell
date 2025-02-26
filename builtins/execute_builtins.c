/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:26:38 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/26 15:42:06 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cmd_name(const char *path)
{
	char	*slash;

	slash = ft_strchr(path, '/');
	if (slash)
		return (get_cmd_name(slash + 1));
	return ((char *)path);
}

void	execute_builtins(char *path, char *args[], t_shell **shell)
{
	char	*cmd_name;

	cmd_name = get_cmd_name(path);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		pwd(shell);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		ft_echo(args, shell);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		cd(args, shell);
	else if (ft_strcmp(cmd_name, "export") == 0)
		ft_export(args, shell);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		ft_unset(args, shell);
	else if (ft_strcmp(cmd_name, "env") == 0)
		print_env(*shell);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		ft_exit(args, shell);
	// else
	// {
	// 	ft_putstr_fd(STDERR_FILENO, "bash: :command not found\n");
	// 	(*shell)->exit_status = COMMAND_NOT_FOUND;
	// }
}
