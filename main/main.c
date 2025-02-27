/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:17:53 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 17:24:44 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	int		is_interactive;
	t_shell	*shell;

	gc_init();
	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	is_interactive = isatty(fileno(stdin));
	if ((argc != 1 && is_interactive) || *argv == NULL)
		return (2);
	init_shell(&shell, env);
	delete_node_by_key(&shell, "OLDPWD");
	shell_loop(&shell);
	if (is_interactive)
		clear_history();
	gc_shutdown();
}
