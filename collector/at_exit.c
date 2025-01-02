/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:44:11 by iziane            #+#    #+#             */
/*   Updated: 2025/01/02 17:07:24 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	remove_empty_nodes(void)
{
	t_gc_node	*current;
	t_gc_node	*temp;
	t_gc_node	*prev;
	t_garbage_collector	*gc;

	gc = get_gc();
	printf("gc->size = %zu\n", gc->size);
	current = gc->head;
	prev = NULL;
	while (current)
	{
		if (current->pointer == NULL)
		{
			printf("im in\n");
			temp = current->next;
			if (current == gc->head)
				gc->head = temp;
			if (prev)
				prev->next = temp;
			free(current);
			gc->size--;
			current = temp;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	printf("gc->size = %zu\n", gc->size);
	gc->tail = prev;
}

// void	main_cleanup(uint8_t exit_stat)
void	main_cleanup(void)
{
	gc_free_all();
	bzero(get_gc(), sizeof(t_garbage_collector));
	// exit(exit_stat);
	// exit(0);
}

void	ft_error(char *msg, char *file, int line, uint8_t exit_stat)
{
	(void)exit_stat;
	fprintf(stderr, "Error: File %s line %d: %s\n", file, line, msg);
	// main_cleanup(exit_stat);
	main_cleanup();
}
