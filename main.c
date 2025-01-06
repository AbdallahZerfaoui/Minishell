/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:17:53 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/06 20:34:08 by azerfaou         ###   ########.fr       */
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
			perror("open");
			return(OPEN_ERROR);
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
		if (fd_out == -1)
		{
			perror("open");
			return (OPEN_ERROR);
		}
	}
	return (fd_out);
}

t_cmd_manager	*prepare_execution(t_cmd_node *cmds, char **env)
{
	t_cmd_manager	*cmd_manager;
	t_cmd_node		*current;
	int				i;

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
		if (access(current->cmd_array[0], X_OK) == 0)
			cmd_manager->cmds[i].path = ft_strdup(current->cmd_array[0]);
		else
			cmd_manager->cmds[i].path = get_command_path(current->cmd_array[0], env);
		cmd_manager->cmds[i].args = current->cmd_array;
		cmd_manager->cmds[i].fd_in = get_fd_in(current);
		cmd_manager->cmds[i].fd_out = get_fd_out(current);
		current = current->next;
		i++;
	}
	cmd_manager->env = env;
	cmd_manager->cmds_lst = cmds;
	// cmd_manager->fd_in = -1;
	// cmd_manager->fd_out = -1;
	return (cmd_manager);
}

char	*read_and_validate_input(void)
{
	char	*line;
	char	*trimmed_line;

	if (isatty(fileno(stdin)))
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
	add_history(line);
	return (line);
}


static void	shell_loop(char **env)
{
	char			*line;
	// char			*trimmed_line;
	t_token			*tokens;
	t_cmd_node		*cmds;
	t_cmd_manager	*cmd_manager;
	// int 			i;
	// t_garbage_collector	*gc;

	// (void)i;
	// (void)env;
	// (void)cmds;
	// (void)cmd_manager;
	// i = 0;
	// gc = gc_init_garbage_collector();
	gc_init_garbage_collector();
	// int fd = open("tests.txt", O_RDONLY);
	while (1)
	{
		// line = ft_strtrim(line, "\n");
		// printf("line = *%s*\n", line);
		// remove_empty_nodes();
		// isatty(fileno(stdin))
		// if (isatty(fileno(stdin)))
		// {
		// 	line = readline(MAGENTA"Minishell> "RESET);
		// 	// line = ft_strdup("/bin/echo $\"42$\"");
		// 	line = ft_strtrim(line, " \n");
		// 	if (!line)
		// 		break ;
		// }
		// else
		// {
		// 	line = get_next_line(fileno(stdin));
		// 	if (!line || line[0] == '\0')
		// 		break ;
		// 	trimmed_line = ft_strtrim(line, "\n");
		// 	if (!trimmed_line)
		// 		break ;
		// 	line = trimmed_line;
		// }
		// if (!line)
		// 	break ;
		// if (ft_strcmp(line, "exit") == 0)
		// 	break ;
		// if (line[0] == '\0')
		// 	continue;
		// if (unbalanced_quotes(line))
		// {
		// 	printf(RED"Unbalanced quotes\n"RESET);
		// 	continue;
		// }
		// if (line[0] != '\0')
		// 	add_history(line);
		line = read_and_validate_input();
		if (ft_strcmp(line, "exit") == 0)
			break ;
		if (!line || line[0] == '\0')
			continue ;
		tokens = lexer(line);
		// t_token *tmp = tokens;
		// while (tmp)
		// {
		// 	printf("value = %s - %d\n", tmp->value, tmp->need_expand);
		// 	tmp = tmp->next;
		// }
		// printf("im here\n");
		tokens = expand(tokens, env);
		cmds = parse(tokens);
		cmd_manager = prepare_execution(cmds, env);
		if (!cmd_manager)
			return ;
		initialize_pipes(cmd_manager);
		create_cmd_processes(cmd_manager);
		wait_for_children(cmd_manager->nbr_cmds);
		close_pipes(cmd_manager);
		// free_tokens(tokens);
		// while (cmds)
		// {
		// 	free_tokens(cmds->cmd);
		// 	free_tokens(cmds->files);
		// 	printf("index = %d\n", cmds->index);
		// 	cmds = cmds->next;
		// }
		// free_cmds(cmds);
		// free_cmd_manager(cmd_manager);
		// if (line)
		// 	free(line);
		// i++;
		// (void)tokens;
	// printf("line = *%s*\n", line);
	}
	// close(fd);
	// printf("end loop\n");
	// my_gc_free_all();
	// main_cleanup();

	// printf("size = %zu\n", gc->size);
	// while (gc->head && gc->head->pointer)
	// {
	// 	// printf("pointer = %s\n", (char *)gc->head->pointer);
	// 	if (gc->head->pointer)
	// 		free(gc->head->pointer);
	// 	gc->head = gc->head->next;
	// }
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
	if (argc != 1 || *argv == NULL)
		return (2);
	shell_loop(env);
	clear_history();
	main_cleanup();
	// memset((void *)get_gc(), 0, sizeof(t_garbage_collector));
	return (0);
}

