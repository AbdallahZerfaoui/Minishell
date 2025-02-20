/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:17:53 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/20 23:22:22 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_waiting_for_input = 1;

int	get_fd_in(t_cmd_node *node)
{
	t_token	*current;
	int		fd_in;

	fd_in = STDIN_FILENO;
	current = node->files;
	while (current && current->next)
	{
		if (current->type == INFILE)
		{
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			if (access(current->next->value, F_OK) == -1)
				return (-1);
			fd_in = open(current->next->value, O_RDONLY);
		}
		current = current->next->next;
	}
	return (fd_in);
}

int	get_fd_out(t_cmd_node *node)
{
	t_token	*current;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	current = node->files;
	while (current && current->next)
	{
		if (current->type == OUTFILE)
		{
			if (fd_out != STDOUT_FILENO && fd_out != -1)
				close(fd_out);
			fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (current->type == APPEND)
		{
			if (fd_out != STDOUT_FILENO && fd_out != -1)
				close(fd_out);
			fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		current = current->next;
	}
	return (fd_out);
}

t_heredoc	*init_heredoc_struct(char *stop_word,
				char *hd_filename, t_shell **shell)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->stop_word = ft_strdup(expand_word(stop_word, *shell));
	heredoc->filename = ft_strdup(hd_filename);
	heredoc->shell = shell;
	return (heredoc);
}

t_cmd_manager	*prepare_execution(t_cmd_node *cmds, t_shell **shell)
{
	t_cmd_manager	*cmd_manager;
	t_cmd_node		*current;
	int				i;
	char			*hd_filename;
	char			*custom_cmd_path;
	t_heredoc		*heredoc;
	t_token			*file;

	cmd_manager = (t_cmd_manager *)ft_calloc(1, sizeof(t_cmd_manager));
	if (!cmd_manager)
		return (NULL);
	cmd_manager->nbr_cmds = len_cmds_lst(cmds);
	cmd_manager->cmds = (t_command *)ft_calloc(cmd_manager->nbr_cmds, sizeof(t_command));
	if (!cmd_manager->cmds)
		return (NULL);
	current = cmds;
	i = 0;
	while (current)
    {
        file = current->files;
        while (file)
        {
            if (file->type == HEREDOC && file->next)
            {
                hd_filename = generate_heredoc_filename();
                heredoc = init_heredoc_struct(file->next->value, hd_filename, shell);
                heredoc_loop(heredoc);
				cmd_manager->cmds[i].hd_filename = heredoc->filename;
            }
            file = file->next;
        }
        i++;
        current = current->next;
    }
	current = cmds;
	i = 0;
	while (current)
	{
		if (current->cmd_array && current->cmd_array[0])
		{
			custom_cmd_path = get_command_path(current->cmd_array[0], (*shell)->env); //TODO get command already does this check
			// dprintf(2, "i : %d -> custom_cmd_path = %s\n", i, custom_cmd_path);
			if (access(current->cmd_array[0], X_OK) == 0 && !custom_cmd_path)
				cmd_manager->cmds[i].path = ft_strdup(current->cmd_array[0]);
			else
				cmd_manager->cmds[i].path = custom_cmd_path;
			cmd_manager->cmds[i].args = current->cmd_array;
		}
		cmd_manager->cmds[i].fd_in = get_fd_in(current);
		cmd_manager->cmds[i].fd_out = get_fd_out(current);
		current = current->next;
		i++;
	}
	cmd_manager->shell = shell;
	cmd_manager->cmds_lst = cmds;
	return (cmd_manager);
}

char	*read_and_validate_input(int is_interactive)
{
	char	*line;
	char	*trimmed_line;

	if (is_interactive)
	{
		line = readline(MAGENTA "Minishell> " RESET);
		line = ft_strtrim(line, " \n");
		if (!line)
			return (NULL);
	}
	else
	{
		line = get_next_line(fileno(stdin));
		if (!line)
			return ("exit"); //TODO improve this shit
		trimmed_line = ft_strtrim(line, "\n");
		if (!trimmed_line)
			return ("exit");
		line = trimmed_line;
	}
	g_waiting_for_input = 0;
	if (!line)
		return (NULL);
	if (unbalanced_quotes(line))
	{
		printf(RED "Unbalanced quotes\n" RESET);
		return ("");
	}
	if (is_interactive)
		add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	int		is_interactive;
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	is_interactive = isatty(fileno(stdin));
	if ((argc != 1 && is_interactive) || *argv == NULL)
		return (2);
	init_shell(&shell, env);
	shell_loop(&shell);
	if (is_interactive)
		clear_history();
	main_cleanup();
	return (0);
}
