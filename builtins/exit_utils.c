/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:38:07 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/18 21:26:59 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	handle_exit_error_message(t_shell **shell, char *message)
{
	if (message)
		ft_putstr_fd(STDERR_FILENO, message);
	(*shell)->exit_status = 255;
}

int	handle_too_many_arguments(char *args[], t_shell *shell)
{
	ft_putstr_fd(STDERR_FILENO, "bash: exit: too many arguments\n");
	if (!ft_isdigit(args[1][0]))
		shell->exit_status = 255;
	else
		shell->exit_status = 1;
	return (shell->exit_status);
}

void	validate_exit_argument(char *arg, t_shell **shell)
{
	char	*expanded;
	char	*message;

	expanded = expand_word(arg, *shell);
	if (!expanded && arg)
	{
		message = "bash: exit: numeric argument required\n";
		handle_exit_error_message(shell, message);
	}
	else if (expanded && !ft_isdigit(*expanded)
		&& !are_only_digits(expanded + 1))
	{
		message = "bash: exit: numeric argument required\n";
		handle_exit_error_message(shell, message);
	}
	else if (expanded && ft_atoi(expanded) == 0)
	{
		if (ft_strcmp(expanded, "0") == 0 || ft_strcmp(expanded, "+0") == 0)
			(*shell)->exit_status = 0;
		else
			(*shell)->exit_status = 255;
	}
	else if (expanded != NULL)
		(*shell)->exit_status = ft_atoi(expanded);
}
