/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:46:07 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/22 20:29:23 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_num_digits(int num)
{
	size_t	nbr_digits;

	nbr_digits = 1;
	if (num < 0)
		nbr_digits++;
	num = num / 10;
	while (num != 0)
	{
		num = num / 10;
		nbr_digits++;
	}
	return (nbr_digits);
}

char	*ft_itoa(int value)
{
	char	*start_ptr;
	char	*end_ptr;
	int		sign;
	size_t	nbr_digits;

	nbr_digits = ft_num_digits(value);
	end_ptr = ft_calloc(nbr_digits + 1, sizeof(char));
	if (!end_ptr)
		return (NULL);
	start_ptr = end_ptr;
	end_ptr += nbr_digits - 1;
	sign = -1 * (value < 0) + (value >= 0);
	if (value == 0)
	{
		*end_ptr = '0';
		return (start_ptr);
	}
	while (value != 0)
	{
		*end_ptr-- = '0' + (value % 10) * sign;
		value /= 10;
	}
	if (sign == -1)
		*end_ptr = '-';
	return (start_ptr);
}
