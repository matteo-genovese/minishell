/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:35:17 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/19 17:50:13 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	integer_len(int n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int number)
{
	char		*str;
	int			len;
	long int	n;

	n = (long int) number;
	len = integer_len(n);
	str = (char *)malloc(integer_len(n) + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	str[len] = 0;
	if (!str)
		return (NULL);
	if (!n)
		str[--len] = '0';
	while (n)
	{
		str[--len] = '0' + n % 10;
		n /= 10;
	}
	return (str);
}
