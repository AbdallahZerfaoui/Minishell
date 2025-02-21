/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:22:28 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/21 22:05:31 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_loop(t_shell **shell)
{
	char			*line;
	t_token			*tokens;
	t_cmd_node		*cmds;
	t_cmd_manager	*cmd_manager;
	int				is_interactive;
	int				status;

	gc_init_garbage_collector();
	update_shlvl(shell);
	is_interactive = isatty(fileno(stdin));
	while (1)
	{
		setup_signals();
		line = read_and_validate_input(is_interactive);
		if (line == NULL)
			break ;
		else if (line[0] == '\0')
			continue ;
		tokens = lexer(line);
		(*shell)->hd_must_expand = set_heredoc_expansion_flag(tokens);
		tokens = expand(tokens, shell);
		tokens = handle_standalone_redirections(tokens, shell);
		if (!tokens)
			continue ;
		if (check_tokens(tokens, shell) != 0)
			continue ;
		cmds = parse(tokens, shell);
		if (check_cmds(cmds, shell) != 0)
			continue ;
		cmd_manager = prepare_execution(cmds, shell);
		if (!cmd_manager)
			continue ;
		initialize_pipes(cmd_manager);
		execute(cmd_manager);
		if (cmd_manager->nbr_cmds > 1)
			wait_for_children(cmd_manager);
		else
		{
			status = 0; //dont let this be uninitialized
			wait(&status);
			if ((*shell)->exit_status == 0)
				(*shell)->exit_status = status >> 8 & 0xFF;
		}
		close_pipes(cmd_manager);
	}
}
