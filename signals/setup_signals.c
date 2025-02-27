/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:24:51 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 16:59:26 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_signals(void)
{
	struct sigaction	sa_sigint;
	struct termios		termios_settings;

	sa_sigint = (struct sigaction){};
	ft_memset(&termios_settings, 0, sizeof(termios_settings));
	tcgetattr(STDIN_FILENO, &termios_settings);
	termios_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_settings);
	sa_sigint.sa_handler = parent_signals;
	sigaction(SIGINT, &sa_sigint, NULL);
	signal(SIGQUIT, SIG_IGN);
}
