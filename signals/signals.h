/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:25:02 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/20 22:52:39 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../minishell.h"
# include <signal.h>

void	parent_signals(int sig);
void	setup_signals(void);
void	default_signals(void);

extern volatile sig_atomic_t	g_waiting_for_input;

#endif