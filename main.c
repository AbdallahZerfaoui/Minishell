/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:17:53 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/26 17:13:09 by azerfaou         ###   ########.fr       */
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

// static void	shell_loop(char **env)
// {
// 	char	*line;
// 	t_exe	*exe;

// 	while (1)
// 	{
// 		line = readline(MAGENTA"Minishell> "RESET);
// 		if (!line || ft_strcmp(line, "exit") == 0)
// 			break ;
// 		if (line[0] != '\0')
// 			add_history(line);
// 		exe = parse_line(line, env);
// 		launch(exe);
// 		free(line);
// 	}
// }

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

// int	main(int argc, char **argv, char **env)
// {
// 	(void)argv;
// 	(void)argc;
// 	shell_loop(env);
// 	return (0);
// }

