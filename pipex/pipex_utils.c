/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:27:46 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/31 22:16:38 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"
#include "../minishell.h"

/**
 * This function load the variable cmds with the commands
 * @param argv the arguments
 * @param cmd_manager the structure containing the commands
 * @return void
 * @exit if malloc fails
 */
void	get_commands(char **argv, t_cmd_manager *cmd_manager)
{
	int			i;

	i = 0;
	cmd_manager->cmds = (t_command *)ft_malloc(sizeof(t_command)
			* cmd_manager->nbr_cmds);
	if (!cmd_manager->cmds)
		exit(EXIT_FAILURE);
	while (i < cmd_manager->nbr_cmds)
	{
		cmd_manager->cmds[i].args = ft_split(argv[i + 2], ' ');
		cmd_manager->cmds[i].path = get_command_path
			(cmd_manager->cmds[i].args[0], cmd_manager->env);
		i++;
	}
}

void	initialize_pipes(t_cmd_manager *cmd_manager)
{
	int	i;

	i = 0;
	cmd_manager->pipes = (int **) ft_malloc(sizeof(int *)
			* (cmd_manager->nbr_cmds - 1));
	if (!cmd_manager->pipes)
		exit(MALLOC_ERROR);
	while (i < cmd_manager->nbr_cmds - 1)
	{
		cmd_manager->pipes[i] = (int *) ft_malloc(sizeof(int) * 2);
		if (pipe(cmd_manager->pipes[i]) == -1)
			exit(PIPE_ERROR);
		i++;
	}
}

// void	open_files(int argc, char **argv, t_cmd_manager *cmd_manager)
// {
// 	char	*infile;
// 	char	*outfile;

// 	infile = argv[1];
// 	outfile = argv[argc - 1];
// 	cmd_manager->fd_in = open(infile, O_RDONLY);
// 	if (cmd_manager->fd_in == -1)
// 	{
// 		perror("Error opening input file");
// 		exit(OPEN_ERROR);
// 	}
// 	cmd_manager->fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (cmd_manager->fd_out == -1)
// 	{
// 		perror("Error opening output file");
// 		close(cmd_manager->fd_in);
// 		exit(OPEN_ERROR);
// 	}
// }

/**
 * This function close the pipes that are not used by the child
 * @param nbr_cmds the number of commands
 * @note every wait() call will wait till one child is done
 * after nbr_cmds calls to wait() all the children will be done
 */
void	wait_for_children(int nbr_cmds)
{
	int	i;

	i = 0;
	while (i < nbr_cmds)
	{
		wait(NULL);
		i++;
	}
}
