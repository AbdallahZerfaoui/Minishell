/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:02:33 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/28 22:04:17 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_cmds_lst(t_cmd_node *cmds)
{
	int			len;
	t_cmd_node	*current;

	len = 0;
	current = cmds;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}
