/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:39:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/22 20:17:56 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The calloc() function allocates memory for an array of nmemb elements of
// size bytes each and returns a pointer to the allocated memory.
// The memory is set to zero. If nmemb or size is 0, then calloc() returns
// either NULL, or a unique pointer value that can later be successfully
// passed to free().

// A less known difference is that in operating systems with optimistic memory
// allocation, like Linux, the pointer returned by malloc isn't backed by real
// memory until the program actually touches it.

// calloc does indeed touch the memory (it writes zeroes on it) and thus you'll
// be sure the OS is backing the allocation with actual RAM (or swap).
// This is also why it is slower than malloc (not only does it have to zero it,
// the OS must also find a suitable memory area by possibly swapping out other
// processes)

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = nitems * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
