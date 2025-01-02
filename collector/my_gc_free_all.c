/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gc_free_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:21:31 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/01 22:32:30 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	my_gc_free_all(void)
{
	t_garbage_collector	*gc;
	t_gc_node			*temp;

	gc = get_gc();
	while (gc->head && gc->head->pointer)
	{
		// printf("pointer = %s\n", (char *)gc->head->pointer);
		if (gc->head->pointer)
		{
			free(gc->head->pointer);
			gc->head->pointer = NULL;
		}
		if (gc->head)
		{
			temp = gc->head->next;
			free(gc->head);
			gc->head = NULL;
			gc->size--;
			gc->head = temp;
		}
	}
}
