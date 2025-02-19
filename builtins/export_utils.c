/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:50:20 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/19 13:12:05 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_export_value_to_one(t_env **env_lst)
{
	t_env	*last;

	last = last_node(*env_lst);
	last->export = 1;
}

void	export_invalid_identifier(char *arg, t_shell **shell)
{
	ft_putstr_fd(STDERR_FILENO, "bash: export: `");
	ft_putstr_fd(STDERR_FILENO, arg);
	ft_putstr_fd(STDERR_FILENO, "': not a valid identifier\n");
	(*shell)->exit_status = 1;
}

/***
 * @param this function process the arguments passed to the export command
 */
void	process_export_argument(char *arg, t_shell **shell)
{
	char	**content;
	t_env	*existing;

	content = ft_split(arg, '=');
	if (!content[0] || !is_valid_key(content[0]))
	{
		export_invalid_identifier(arg, shell);
		return ;
	}
	if (ft_strchr(arg, '=') == NULL)
	{
		if (is_valid_key(content[0]))
			add_env_node(&(*shell)->env_lst, arg);
		else
			export_invalid_identifier(arg, shell);
		return ;
	}
	existing = find_node_by_key(content[0], *shell);
	if (existing)
		update_env_node(existing, content[1]);
	else
		add_env_node(&(*shell)->env_lst, arg);
	set_export_value_to_one(&(*shell)->env_lst);
}
