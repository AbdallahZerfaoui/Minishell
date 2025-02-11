/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:02:32 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/11 14:15:04 by azerfaou         ###   ########.fr       */
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
		// env_array[i] = ft_strjoin(tmp->content[0], "=");
		// env_array[i] = ft_strjoin(env_array[i], tmp->content[1]);
		env_array[i] = ft_strjoin_all(tmp->content[0], "=", tmp->content[1], NULL);
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
	// env_lst = (t_env *)ft_calloc(1, sizeof(struct s_env));
	// if (!env_lst)
	// 	return (env_lst);
	env_lst = NULL;
	while (env[i])
	{
		// printf("im in get en lst\n");
		add_env_node(&env_lst, env[i]);
		// printf("env_lst->content[0] = %s\n", env_lst->content[0]);
		i++;
	}
	add_env_node(&env_lst, NULL); // null terminated to know when to stop
	// if (!env_lst)
	// 	printf("env_lst is empty in get env lst\n");
	return (env_lst);
}

/**
 * @brief Print the environment variables
 * @note This function is the main function for the 'env' builtin
 */
void	print_env(t_shell *shell)
{
	int		i;

	i = 0;
	if (!shell->env)
		return ;
	// update_env_array(&shell); //TODO should we update the env array here?
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}

/***
 * @brief This function is used when the user use export without any arguments
 */
void	ft_exp_print(t_env	*env_lst)
{
	t_env	*current;

	current = env_lst;
	if (!current)
	{
		ft_putstr_fd(STDERR_FILENO, "no env found\n");
		return ;
	}
	while (current)
	{
		if (ft_strcmp(current->content[0], "_") == 0)
		{
			current = current->next;
			continue ;
		}
		else if (current->content[0])
			printf("declare -x %s", current->content[0]);
		if (current->content[1] && ft_strcmp(current->content[1], "") != 0)
		{
			printf("=\"%s\"\n", current->content[1]);
		}
		// else if (current->content[1] && ft_strcmp(current->content[1], "") == 0)
		// {
		// 	printf("\n");
		// }
		// else if (current->export == 0)
		// {
		// 	printf("=\"\"\n");
		// }
		else
			printf("\n");
		current = current->next;
	}
}
