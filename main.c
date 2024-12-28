/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:17:53 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/28 16:33:39 by azerfaou         ###   ########.fr       */
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
	// cmd_manager->pipes = (int **)ft_calloc(cmd_manager->nbr_cmds - 1, sizeof(int *));
	// if (!cmd_manager->pipes)
	// 	return (NULL);
	// i = 0;
	// while (i < cmd_manager->nbr_cmds - 1)
	// {
	// 	cmd_manager->pipes[i] = (int *)ft_calloc(2, sizeof(int));
	// 	if (!cmd_manager->pipes[i])
	// 		return (NULL);
	// 	if (pipe(cmd_manager->pipes[i]) == -1)
	// 		return (NULL);
	// 	i++;
	// }
	current = cmds;
	i = 0;
	while (current)
	{
		cmd_manager->cmds[i].path = get_command_path(current->cmd_array[0], env);
		cmd_manager->cmds[i].args = current->cmd_array;
		// set_args(&cmd_manager->cmds[i].args, current->cmd_array);
		current = current->next;
		i++;
	}
	cmd_manager->env = env;
	// cmd_manager->fd_in = -1;
	// cmd_manager->fd_out = -1;
	return (cmd_manager);
}

static void	shell_loop(char **env)
{
	char			*line;
	t_cmd_manager	*cmd_manager;
	// int 			i;

	// (void)env;
	while (1)
	{
		line = readline(MAGENTA"Minishell> "RESET);
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		if (line[0] != '\0')
			add_history(line);
		// exe = parse_line(line, env);
		cmd_manager = prepare_execution(parse(lexer(line)), env);
		if (!cmd_manager)
			return ;
		initialize_pipes(cmd_manager);
		// printf("nbr_cmds = %d\n", cmd_manager->nbr_cmds);
		// printf("cmd[0].path = %s\n", cmd_manager->cmds[0].path);
		// i = 0;
		// while (cmd_manager->cmds[0].args[i])
		// {
		// 	printf("%s ", cmd_manager->cmds[0].args[i]);
		// 	i++;
		// }
		// char *args_tmp[] = {"ls", NULL};
		// execve(cmd_manager->cmds[0].path, cmd_manager->cmds[0].args, env);
		create_cmd_processes(cmd_manager);
		wait_for_children(cmd_manager->nbr_cmds);
		close_pipes(cmd_manager);
		// free_cmd_manager(cmd_manager);
		free(line);
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
	(void)argv;
	(void)argc;
	shell_loop(env);
	return (0);
}

