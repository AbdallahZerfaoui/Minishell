/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:02:32 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/01 14:55:36 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_lst_to_array(t_env *env_lst)
{
	t_env	*tmp;
	char	**env_array;
	int		i;

	i = 0;
	tmp = env_lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_array = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	tmp = env_lst;
	while (tmp)
	{
		env_array[i] = ft_strjoin(tmp->content[0], "=");
		env_array[i] = ft_strjoin(env_array[i], tmp->content[1]);
		i++;
		tmp = tmp->next;
	}
	return (env_array);
}

t_env	*get_env_lst(char **env)
{
	t_env	*env_lst;
	int		i;

	i = 0;
	env_lst = (t_env *)ft_calloc(1, sizeof(struct s_env));
	if (!env_lst)
		return (env_lst);
	while (env[i])
	{
		add_env_node(&env_lst, env[i]);
		i++;
	}
	return (env_lst);
}

void	print_env(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}
