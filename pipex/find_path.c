/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:01:10 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/22 22:06:38 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief This function joins two strings with a '/'
 * @param dir the directory
 * @param cmd the command
 * @return the full path
 */
char	*join_paths(const char *dir, const char *cmd)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (perror("Error"), NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (perror("Error"), NULL);
	return (full_path);
}

/**
 * This function parse the env variable to get the PATH
 * and return it as a tab of strings
 * @param env the env variable
 * @return the PATH
 */
char	**parse_env(char **env)
{
	int		i;
	char	*path;
	char	**split_paths;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			if (!path)
				return (perror("Error"), NULL);
			split_paths = ft_split(path, ':');
			free(path);
			if (!split_paths)
				return (perror("Error"), NULL);
			return (split_paths);
		}
		i++;
	}
	return (NULL);
}

/**
 * This function get the full path of a given command
 * @param cmd the command
 * @param env the env variable
 * @return the full path
 * @note this function will join the path with all the commands
 * and if the path is empty, it will use the default paths
 */
char	*get_command_path(char *cmd, char **env)
{
	char		**paths;
	char		*full_path;
	int			i;
	static char	*default_paths[] = {"/usr/local/bin", "/usr/bin", "/bin", \
			"/usr/sbin", "/sbin", NULL};
	paths = parse_env(env);
	if (!paths)
		paths = default_paths;
	i = 0;
	while (paths[i])
	{
		full_path = join_paths(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (free_all(paths), full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
