/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:37:49 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/08 16:02:43 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	len_args(char **args)
// {
// 	int	len;

// 	len = 0;
// 	while (args[len])
// 		len++;
// 	return (len);
// }

int	are_only_digits(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char *args[], t_shell **shell)
{
	char	*first_arg;	

	if (!args)
	{
		main_cleanup();
		exit(MISUSE_ERROR);
	}
	(*shell)->exit_status = 0; //TODO check if it should be 1 or 0
	first_arg = expand_word(args[1], *shell); // case exit "+100"
	if (!first_arg && args[1])
	{
		ft_putstr_fd(STDERR, "minishell: exit: numeric argument required\n");
		(*shell)->exit_status = 255;
	}
	else if (first_arg && !ft_isdigit(*first_arg) && !are_only_digits(first_arg + 1))
	{
		ft_putstr_fd(STDERR, "minishell: exit: numeric argument required\n");
		(*shell)->exit_status = 255;
	}
	else if (first_arg && ft_atoi(first_arg) == 0)
	{
		if (ft_strcmp(first_arg, "0") == 0 || ft_strcmp(first_arg, "+0") == 0)
			(*shell)->exit_status = 0;
		else
			(*shell)->exit_status = 255;
	}
	else if (len_args(args) > 2)
	{
		ft_putstr_fd(STDERR, "minishell: exit: too many arguments\n");
		(*shell)->exit_status = 1;
		return ;
	}
	else if (first_arg != NULL)
		(*shell)->exit_status = ft_atoi(first_arg);
	main_cleanup();
	exit((*shell)->exit_status);
}
