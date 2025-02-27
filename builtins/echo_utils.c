/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:01:06 by azerfaou          #+#    #+#             */
/*   Updated: 2025/02/27 22:02:34 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/***
 * Returns the number of "-n" flags in the arguments.
 * The "-n" flag is valid if 
 * - it is the first argument 
 * - it is preceded by another "-n" flag.
 */
int	get_n_flag(char *args[])
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1])
		{
			j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == TK_NULL_CHAR)
				i++;
			else
				break ;
		}
		else
			break ;
	}
	return (i);
}
