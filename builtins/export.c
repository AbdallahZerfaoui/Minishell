/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:50:31 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/26 23:51:24 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/***
 * @param this function emulate the export command in bash
 * @param args the arguments passed to the export command
 * @param shell the shell structure
 * how it works:
 * 1. if no arguments are passed, it prints the environment variables
 * 2. if arguments are passed, it checks if the argument is a valid identifier
 * 3. if the argument is a valid identifier,
 * it checks if the argument contains an equal sign
 * 4. if the argument contains an equal sign,
 * it splits the argument into key and value
 * 5. if the key is already in the environment variables, it updates the value
 * 6. if the key is not in the environment variables,
 * it adds the key and value to the environment variables
 * 7. if the key is not a valid identifier, it prints an error message
 */
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
		process_export_argument(args[i], shell);
		i++;
	}
	update_env_array(shell);
}
