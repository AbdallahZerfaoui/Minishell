/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:52:53 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/31 22:31:32 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_result;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str_result = \
		(char *)ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str_result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str_result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str_result[i + j] = s2[j];
		j++;
	}
	str_result[i + j] = '\0';
	return (str_result);
}
