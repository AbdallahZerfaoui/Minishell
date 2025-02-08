/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:50:31 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/08 21:54:58 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_export_value_to_one(t_env **env_lst)
{
	t_env	*last;

	last = last_node(*env_lst);
	last->export = 1;
}

void	ft_export(char *args[], t_shell **shell)
{
	int		i;

	if (!args[1])
	{
		ft_exp_print((*shell)->env_lst);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (ft_isalpha(args[i][0]) == 0 && args[i][0] != '_')
		{
			ft_putstr_fd(STDERR, "export: `");
			ft_putstr_fd(STDERR, args[i]);
			ft_putstr_fd(STDERR, "': not a valid identifier\n");
			(*shell)->exit_status = 1;
			i++;
			continue ;
		}
		if (ft_strchr(args[i], '=') == NULL)
		{
			// args[i] = ft_strjoin(args[i], "="); // TODO are we adding args[i] to the env_lst? test 390
			add_env_node(&(*shell)->env_lst, args[i]);
			i++;
			continue ;
		}
		add_env_node(&(*shell)->env_lst, args[i]);
		set_export_value_to_one(&(*shell)->env_lst); //TODO do i need to set export to 1?
		i++;
	}
	update_env_array(shell);
}

