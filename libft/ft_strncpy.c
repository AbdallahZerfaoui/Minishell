/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:43:09 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/01 18:43:18 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *destination, const char *source, size_t n)
{
	size_t	i;

	i = 0;
	if (!source)
		return (destination);
	while (source[i] && i < n)
	{
		destination[i] = source[i];
		i++;
	}
	while (i < n)
	{
		destination[i] = '\0';
		i++;
	}
	return (destination);
}
