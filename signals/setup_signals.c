/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:24:51 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/19 17:37:37 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_signals(void)
{
	struct sigaction	sa_sigint;
	struct termios		termios_settings;

	sa_sigint = (struct sigaction){};
	tcgetattr(0, &termios_settings);
	termios_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_settings);
	sa_sigint.sa_handler = parent_signals;
	sigaction(SIGINT, &sa_sigint, NULL);
	signal(SIGQUIT, SIG_IGN);
}
