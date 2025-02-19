/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:17:53 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/19 12:46:07 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void	init_g(char **envp, char *input)
// {
// 	g_data.nb_pipe = ms_count_char(input, TK_PIPE);
// 	if (!g_data.envp)
// 	{
// 		g_data.envp = copy_envp(envp);
// 		g_data.exit_status = 0;
// 	}
// }
// void set_args(char ***args, char **cmd_array)
// {
//     int total_args = 0;
//     int i, j;

//     while (cmd_array[total_args])
//         total_args++;

//     if (total_args <= 1)
// 		*args = NULL;

//     // Allocate memory for args (total_args - 1 elements + null terminator)
//     *args = (char **)malloc((total_args) * sizeof(char *));
//     if (!*args)
//         return; // Handle allocation failure

//     // Copy elements from cmd_array[1:] to args
//     for (i = 1, j = 0; i < total_args; i++, j++)
//     {
//         (*args)[j] = strdup(cmd_array[i]); // Copy each string
//     }

//     (*args)[j] = NULL; // Null-terminate the args array
// }
int	get_fd_in(t_cmd_node *node, t_shell **shell)
{
	// t_token	*file;
	t_token	*current;
	int		fd_in;

	(void)shell; //TODO remove this
	fd_in = STDIN_FILENO;
	current = node->files;
	// if (node && node->files && node->files->type == INFILE)
	// {
	// 	file = node->files->next;
	// 	if (access(file->value, F_OK) == -1)
	// 		return (-1);
	// 	fd_in = open(file->value, O_RDONLY);
	// }
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
		// printf("current->value = %s\n", current->value);
    }
	return (fd_in);
}

int	get_fd_out(t_cmd_node *node, t_shell **shell)
{
	// t_token	*file;
	t_token	*current;
	int		fd_out;
	

	(void)shell; //TODO remove this
	fd_out = STDOUT_FILENO;
	current = node->files;
	// while (current)
	// {
	// 	printf("current->value = %s\n", current->value);
	// 	current = current->next;
	// }
	// if (node && node->files && node->files->type == OUTFILE)
	// {
	// 	file = node->files->next;
	// 	fd_out = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// }
	// else if (node && node->files && node->files->type == APPEND)
	// {
	// 	file = node->files->next;
	// 	fd_out = open(file->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// }
	while (current && current->next)
    {
        if (current->type == OUTFILE)
        {
// if (current->prev)
// printf("current->prev->value = %s\n", current->prev->value);
// printf("current->value = %s\n", current->value);
// printf("current->next->value = %s\n", current->next->value);
            if (fd_out != STDOUT_FILENO && fd_out != -1)
                close(fd_out);
            fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        else if (current->type == APPEND)
        {
// if (current->prev)
// printf("current->prev->value = %s\n", current->prev->value);
// printf("current->value = %s\n", current->value);
// printf("current->next->value = %s\n", current->next->value);
            if (fd_out != STDOUT_FILENO && fd_out != -1)
                close(fd_out);
            fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        current = current->next;
    }
	return (fd_out);
}

t_heredoc	*init_heredoc_struct(char *stop_word, char *hd_filename, t_shell **shell)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	// printf("stop_word = %s\n", stop_word);
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
				// ignore_signals();
                hd_filename = generate_heredoc_filename();
                heredoc = init_heredoc_struct(file->next->value, hd_filename, shell);
                heredoc_loop(heredoc);
                // cmd_manager->cmds[i].fd_in = open(hd_filename, O_RDONLY);
				// cmd_manager->cmds[i].hd_filename = ft_strdup(hd_filename);
				cmd_manager->cmds[i].hd_filename = heredoc->filename;
				// printf("fd_in = %d\n", cmd_manager->cmds[i].fd_in);
                // unlink(hd_filename);  // Delete temp file after opening
                // free(hd_filename);
            }
			// else if (file->type == INFILE && file->next
			// 	&& current->cmd == NULL)
			// {
			// 	int tmp_fd = open(file->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			// 	close(tmp_fd);
			// 	cmds = current->next;
			// }
            file = file->next;
        }
        i++;
        current = current->next;
    }
	current = cmds;
	i = 0;
	while (current)
	{
		// printf("current index = %d -> %s\n", current->index, current->files->value);
		if (current->cmd_array && current->cmd_array[0])
		{
			custom_cmd_path = get_command_path(current->cmd_array[0], (*shell)->env); //TODO get command already does this check
			if (access(current->cmd_array[0], X_OK) == 0 && !custom_cmd_path)
				cmd_manager->cmds[i].path = ft_strdup(current->cmd_array[0]);
			else
				cmd_manager->cmds[i].path = custom_cmd_path;
			cmd_manager->cmds[i].args = current->cmd_array;
		}
		// if (cmds->files
		// 	&& (current->files->type == INFILE || current->files->type == OUTFILE))
		// {
		// 	cmd_manager->cmds[i].fd_in = get_fd_in(current);
		// 	cmd_manager->cmds[i].fd_out = get_fd_out(current);
		// }
		// if (current->files && current->files
		// 	&& current->files->type == HEREDOC)
		// {
			// hd_filename = generate_heredoc_filename();
			// if (current->files->next)
			// {
			// 	heredoc = init_heredoc_struct
			// 		(current->files->next->value, hd_filename, shell);
			// 	heredoc_loop(heredoc); //this is the stop word for the heredoc
			// }
			// else
			// {
			// 	ft_putstr_fd(STDERR_FILENO, "bash: syntax error\n");
			// 	return (NULL);
			// 	// (*shell)->exit_status = HEREDOC_ERROR;
			// 	// exit(HEREDOC_ERROR);
			// }
			// cmd_manager->cmds[i].fd_in = open(hd_filename, O_RDONLY);
			// // if (cmd_manager->cmds[i].fd_in == -1)
			// // {
			// // 	ft_putstr_fd(STDERR_FILENO, "bash: heredoc create error");
			// // 	(*shell)->exit_status = OPEN_ERROR;
			// // 	exit(OPEN_ERROR); //TODO change this to a better error
			// // }
			// cmd_manager->cmds[i].fd_out = get_fd_out(current, shell);
		// }
		// else
		// {
		// if (cmd_manager->cmds[i].fd_in == -1)
		cmd_manager->cmds[i].fd_in = get_fd_in(current, shell);
		// printf("cmd_manager->cmds[i].fd_in = %d\n", cmd_manager->cmds[i].fd_in);
		cmd_manager->cmds[i].fd_out = get_fd_out(current, shell);
			// if (cmd_manager->cmds[i].fd_in == -1
			// 	|| cmd_manager->cmds[i].fd_out == -1)
			// {
			// 	ft_putstr_fd(STDERR_FILENO, "No such file or directory\n");
			// 	(*shell)->exit_status = OPEN_ERROR;
			// 	return (NULL);
			// 	// return (NULL);
			// }
		// }
		// if (cmds->files
		// 	&& current->files->type == OUTFILE)
		// {
		// cmd_manager->cmds[i].fd_out = get_fd_out(current);
		// }
		// if (current->files)
		// 	printf("type = %d\n", current->files->type);
		current = current->next;
		i++;
	}
	// cmd_manager->env = env;
	cmd_manager->shell = shell;
	cmd_manager->cmds_lst = cmds;
	// cmd_manager->fd_in = -1;
	// cmd_manager->fd_out = -1;
	return (cmd_manager);
}

char	*read_and_validate_input(int is_interactive)
{
	char	*line;
	char	*trimmed_line;
	g_waiting_for_input = 1;

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
	// if (ft_strcmp(line, "exit") == 0)
	// 	return ("exit"); //is it the right way to handle exit?
	// if (line[0] == '\0')
	// 	return ("");
	if (unbalanced_quotes(line))
	{
		printf(RED "Unbalanced quotes\n" RESET);
		return ("");
	}
	if (is_interactive)
		add_history(line);
	return (line);
}

static void	shell_loop(t_shell **shell)
{
	char			*line;
	t_token			*tokens;
	t_cmd_node		*cmds;
	t_cmd_manager	*cmd_manager;
	int				is_interactive;

	gc_init_garbage_collector();
	is_interactive = isatty(fileno(stdin));
	while (1)
	{
setup_signals();
		line = read_and_validate_input(is_interactive);
		// if (ft_strcmp(line, "exit") == 0)
		// 	ft_exit(shell);
		// if (line[0] == '\0')
		// 	printf("line = %s\n", line);
		// printf("ctrl_c_pressed = %d\n", ctrl_c_pressed);
		if (line == NULL)
			break ;
		else if (line[0] == '\0')
			continue ;
		tokens = lexer(line);
		(*shell)->hd_must_expand = set_heredoc_expansion_flag(tokens);
		// printf("hd_must_expand = %d\n", (*shell)->hd_must_expand);
		// printf("line = %s\n", line);
		tokens = expand(tokens, shell);
		tokens = handle_standalone_redirections(tokens, shell);
		if (!tokens)
			continue ;
		if (check_tokens(tokens, shell) != 0)
			continue ;
		// for (t_token *tmp = tokens; tmp; tmp = tmp->next)
		// 	printf("value = *%s*\n", tmp->value);
		cmds = parse(tokens, shell);
		if (check_cmds(cmds, shell) != 0)
			continue ;
		cmd_manager = prepare_execution(cmds, shell);
		if (!cmd_manager)
			continue ;
		initialize_pipes(cmd_manager);
		create_cmd_processes(cmd_manager);
		// printf("exit_status = %d\n", (*shell)->exit_status);
		if (cmd_manager->nbr_cmds > 1)
			wait_for_children(cmd_manager);
		else
		{
			int	status = 0; //dont let this be uninitialized
			wait(&status);
			// status = status >> 8 & 0xFF;
			// if (WIFEXITED(status))
			if ((*shell)->exit_status == 0)
				(*shell)->exit_status = status >> 8 & 0xFF;
			// (*shell)->exit_status = status >> 8 & 0xFF;
			// else
			// 	(*shell)->exit_status = 17;
		}
			// waitpid(cmd_manager->pid, &(*shell)->exit_status, 0);
		// wait_for_children(cmd_manager);
		close_pipes(cmd_manager);
// print_env(*shell);
// for (t_env *tmp = (*shell)->env_lst; tmp; tmp = tmp->next)
// 	printf("key = %s\n", tmp->content[0]);
	}
}

// static void    shell_loop(char **envp)
// {
// 	char	*input;
// 	t_exe	*exe;

// 	while (true)
// 	{
// 		printf(MAGENTA);
// 		termios_echoback(false);

// 		input = ft_strtrim(readline("Minishell➜  "), " \t");
// 		if (input && input[0])
// 		{
// 			add_history(input);
// 			init_g(envp, input);
// 			exe = ms_init(input);
// 			// exe = parse_line(input, envp);
// 			if (!exe)
// 				ms_exit(QLAWI_ERR);
// 			// dprintf(2, "fd = %d\n", exe[1].fd_in);
// 			launch(exe);
// 			if (!ft_strncmp(input, "exit", ft_strlen("exit") + 1))
// 				break;
// 			//system("leaks minishell");
// 		}
// 		else if (input == NULL)
// 			break ;
// 	}
// 	printf(RESET);
// }

int	main(int argc, char **argv, char **env)
{
	int		is_interactive;
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	is_interactive = isatty(fileno(stdin));
	// printf("is_interactive = %d\n", is_interactive);
	if ((argc != 1 && is_interactive) || *argv == NULL)
		return (2);
	init_shell(&shell, env);
	update_shlvl(&shell);
	shell_loop(&shell);
	if (is_interactive)
		clear_history();
	main_cleanup();
	return (0);
}

