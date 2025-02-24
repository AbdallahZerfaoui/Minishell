/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:37:49 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/24 19:39:32 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char *args[], t_shell **shell)
{
	int		status;

	if (!args)
	{
		gc_shutdown();
		exit(MISUSE_ERROR);
	}
	else if (len_args(args) > 2)
	{
		handle_too_many_arguments(args, *shell);
		return ;
	}
	validate_exit_argument(args[1], shell);
	status = (*shell)->exit_status;
	gc_shutdown();
	exit(status);
}
