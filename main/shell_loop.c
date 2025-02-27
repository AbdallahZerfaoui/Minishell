/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:22:28 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 17:17:33 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commands(t_cmd_manager *cmd_manager, t_shell **shell)
{
	int	status;

	initialize_pipes(cmd_manager);
	execute(cmd_manager);
	if (cmd_manager->nbr_cmds > 1)
		wait_for_children(cmd_manager);
	else
	{
		status = 0;
		wait(&status);
		if ((*shell)->exit_status == 0)
			(*shell)->exit_status = status >> 8 & 0xFF;
	}
	close_pipes(cmd_manager);
}

/***
 * @brief This function is the main function that will process the line.
 * @param line
 * @param shell
 */
void	process_line(char *line, t_shell **shell)
{
	t_token			*tokens;
	t_cmd_node		*cmds;
	t_cmd_manager	*cmd_manager;

	tokens = lexer(line);
	(*shell)->hd_must_expand = set_heredoc_expansion_flag(tokens);
	tokens = expand(tokens, shell);
	tokens = handle_standalone_redirections(tokens, shell);
	if (!tokens || check_tokens(tokens, shell) != 0)
		return ;
	cmds = parse(tokens, shell);
	if (check_cmds(cmds, shell) != 0)
		return ;
	cmd_manager = prepare_execution(cmds, shell);
	if (!cmd_manager)
		return ;
	execute_commands(cmd_manager, shell);
}

void	shell_loop(t_shell **shell)
{
	char			*line;
	int				is_interactive;

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
		process_line(line, shell);
	}
}
