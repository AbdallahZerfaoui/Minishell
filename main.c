/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:17:53 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/06 19:15:16 by azerfaou         ###   ########.fr       */
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
int	get_fd_in(t_cmd_node *node)
{
	t_token	*file;
	int		fd_in;

	fd_in = STDIN_FILENO;
	if (node && node->files && node->files->type == INFILE)
	{
		file = node->files->next;
		fd_in = open(file->value, O_RDONLY);
		if (fd_in == -1)
		{
			perror("open error");
			exit(OPEN_ERROR);
		}
	}
	return (fd_in);
}

int	get_fd_out(t_cmd_node *node)
{
	t_token	*file;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	if (node && node->files && node->files->type == OUTFILE)
	{
		file = node->files->next;
		fd_out = open(file->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (node && node->files && node->files->type == APPEND)
	{
		file = node->files->next;
		fd_out = open(file->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd_out == -1)
	{
		perror("open error");
		exit(OPEN_ERROR);
	}
	return (fd_out);
}

t_cmd_manager	*prepare_execution(t_cmd_node *cmds, t_shell **shell)
{
	t_cmd_manager	*cmd_manager;
	t_cmd_node		*current;
	int				i;
	char			*hd_filename;

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
		// printf("current index = %d -> %s\n", current->index, current->files->value);
		if (current->cmd_array && current->cmd_array[0])
		{
			if (access(current->cmd_array[0], X_OK) == 0)
				cmd_manager->cmds[i].path = ft_strdup(current->cmd_array[0]);
			else
				cmd_manager->cmds[i].path = get_command_path(current->cmd_array[0], (*shell)->env);
			cmd_manager->cmds[i].args = current->cmd_array;
		}
		// if (cmds->files
		// 	&& (current->files->type == INFILE || current->files->type == OUTFILE))
		// {
		// 	cmd_manager->cmds[i].fd_in = get_fd_in(current);
		// 	cmd_manager->cmds[i].fd_out = get_fd_out(current);
		// }
		if (cmds->files && current->files
			&& current->files->type == HEREDOC)
		{
			hd_filename = generate_heredoc_filename();
			if (current->files->next)
				heredoc_loop(current->files->next->value, hd_filename); //this is the stop word for the heredoc
			else
			{
				fprintf(stderr, "bash: syntax error\n");
				// exit(HEREDOC_ERROR);
			}
			cmd_manager->cmds[i].fd_in = open(hd_filename, O_RDONLY);
			if (cmd_manager->cmds[i].fd_in == -1)
			{
				perror("heredoc create error");
				exit(OPEN_ERROR);
			}
			cmd_manager->cmds[i].fd_out = get_fd_out(current);
		}
		else
		{
			cmd_manager->cmds[i].fd_in = get_fd_in(current);
			cmd_manager->cmds[i].fd_out = get_fd_out(current);
		}
		// if (cmds->files
		// 	&& current->files->type == OUTFILE)
		// {
		// cmd_manager->cmds[i].fd_out = get_fd_out(current);
		// }
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

	if (is_interactive)
	{
		line = readline(MAGENTA "Minishell> " RESET);
		line = ft_strtrim(line, " \n");
		if (!line)
			return ("");
	}
	else
	{
		line = get_next_line(fileno(stdin));
		if (!line || line[0] == '\0')
			return ("exit");
		trimmed_line = ft_strtrim(line, "\n");
		if (!trimmed_line)
			return ("exit");
		line = trimmed_line;
	}
	if (!line)
		return (NULL);
	if (ft_strcmp(line, "exit") == 0)
		return ("exit"); //is it the right way to handle exit?
	if (line[0] == '\0')
		return ("");
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
		line = read_and_validate_input(is_interactive);
		// if (ft_strcmp(line, "exit") == 0)
		// 	ft_exit(shell);
		if (!line || line[0] == '\0')
			continue ;
		tokens = lexer(line);
		// printf("line = %s\n", line);
		tokens = expand(tokens, *shell);
		// for (t_token *tmp = tokens; tmp; tmp = tmp->next)
		// 	printf("value = *%s*\n", tmp->value);
		cmds = parse(tokens);
		cmd_manager = prepare_execution(cmds, shell);
		if (!cmd_manager)
			return ;
		initialize_pipes(cmd_manager);
		create_cmd_processes(cmd_manager);
		// print_env(shell); //TODO remove this line
		// printf("command : %s\n", cmd_manager->cmds->path);
		// printf("args : %s\n", cmd_manager->cmds->args[1]);
		// printf("args : %s\n", cmd_manager->cmds->args[2]);
		// printf("args : %s\n", cmd_manager->cmds->args[3]);
		// printf("args : %s\n", cmd_manager->cmds->args[4]);
		// printf("args : %s\n", cmd_manager->cmds->args[5]);
		wait_for_children(cmd_manager->nbr_cmds);
		close_pipes(cmd_manager);
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
	shell_loop(&shell);
	if (is_interactive)
		clear_history();
	main_cleanup();
	return (0);
}

