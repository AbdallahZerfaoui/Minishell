/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:04:47 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/04 20:54:58 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"
#include "../minishell.h"

void	free_cmd_manager(t_cmd_manager *cmd_manager)
{
	int	i;

	i = 0;
	while (i < cmd_manager->nbr_cmds)
	{
		free_all(cmd_manager->cmds[i].args);
		free(cmd_manager->cmds[i].path);
		i++;
	}
	free(cmd_manager->cmds);
	i = 0;
	while (i < cmd_manager->nbr_cmds - 1)
	{
		free(cmd_manager->pipes[i]);
		i++;
	}
	free(cmd_manager->pipes);
}

/**
 * This function closes the unused pipes
 * if i != chd_nbr - 1, close the read end
 * if i != chd_nbr, close the write end
 * @note need to handle errors of close
 */
void	close_unused_pipes(int **pipes, int nbr_cmds, int chd_nbr)
{
	int	i;

	i = 0;
	while (i < nbr_cmds - 1) //i =0 ch =1
	{
		if (i != chd_nbr - 1)
		{
			close(pipes[i][0]);
		}
		if (i != chd_nbr)
		{
			close(pipes[i][1]);
		}
		i++;
	}
}

/**
 * This function closes the pipes
 * @param cmd_manager the structure containing the pipes
 * it closes every pipe
 * 0 is the read end
 * 1 is the write end
 */
void	close_pipes(t_cmd_manager *cmd_manager)
{
	int	i;

	i = 0;
	while (i < cmd_manager->nbr_cmds - 1)
	{
		close(cmd_manager->pipes[i][1]);
		close(cmd_manager->pipes[i][0]);
		i++;
	}
}

/**
 * the parent process will loop and create nbr_cmds children
 * one for each command
 * the first child will read from the input file and write to the pipe
 * the last child will read from the pipe and write to the output file
 * the middle children will read from the pipe and write to the next one
 */
void	create_cmd_processes(t_cmd_manager *cmd_manager)
{
	int	chd_nbr;

	chd_nbr = 0;
	while (chd_nbr < cmd_manager->nbr_cmds)
	{
		cmd_manager->pid = fork();
		if (cmd_manager->pid == -1)
		{
			perror("fork error");
			exit(FORK_ERROR);
		}
		if (cmd_manager->pid == 0) // 0 is the child
		{
			if (chd_nbr == 0)
				handle_first_child(cmd_manager, chd_nbr);
			else if (chd_nbr == cmd_manager->nbr_cmds - 1)
				handle_last_child(cmd_manager, chd_nbr);
			else
				handle_mid_children(cmd_manager, chd_nbr && cmd_manager->nbr_cmds > 2);
			if (execve(cmd_manager->cmds[chd_nbr].path,
					cmd_manager->cmds[chd_nbr].args, cmd_manager->env) == -1)
				exit(EXIT_FAILURE);
		}
		chd_nbr++;
	}
	close_unused_pipes(cmd_manager->pipes, cmd_manager->nbr_cmds, chd_nbr);
}

/*
* This function do the following:
* 1. Check if the number of arguments is correct (4)
* 2. Get the commands from the arguments
* 3. Open the files, input and output
* 4. Initialize the pipes
* 5. Create the command processes which is the main part of the program
* 6. Close the pipes after the processes are done
* 7. Wait for the children to finish
*@note: this function works with exactly 4 arguments
*test 1: ./pipex infile "cat" "sort -r" "wc -l" outfile
*test 2: ./pipex infile "grep a1" "wc -l" outfile
*/
// int	main(int argc, char **argv, char **env)
// {
// 	t_cmd_manager	cmd_manager;

// 	handle_arguments(argc);
// 	cmd_manager.env = env;
// 	cmd_manager.nbr_cmds = argc - 3;
// 	get_commands(argv, &cmd_manager);
// 	open_files(argc, argv, &cmd_manager);
// 	initialize_pipes(&cmd_manager);
// create_cmd_processes(&cmd_manager);
// 	close_pipes(&cmd_manager);
// 	wait_for_children(cmd_manager.nbr_cmds);
// 	// free_cmd_manager(&cmd_manager);
// 	return (0);
// }
