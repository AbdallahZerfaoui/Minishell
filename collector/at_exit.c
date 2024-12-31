/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:44:11 by iziane            #+#    #+#             */
/*   Updated: 2024/12/31 22:18:31 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

// void	main_cleanup(uint8_t exit_stat)
void	main_cleanup(void)
{
	gc_free_all();
	bzero(get_gc(), sizeof(t_garbage_collector));
	// exit(exit_stat);
	exit(0);
}

void	ft_error(char *msg, char *file, int line, uint8_t exit_stat)
{
	(void)exit_stat;
	fprintf(stderr, "Error: File %s line %d: %s\n", file, line, msg);
	// main_cleanup(exit_stat);
	main_cleanup();
}
