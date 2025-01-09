/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:44:06 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/17 17:23:30 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (!n)
		return (NULL);
	while (--n)
	{
		if (*((unsigned char *)s) == (unsigned char)c)
			return ((void *)s);
		s++;
	}
	if (*((unsigned char *)s) == (unsigned char) c)
		return ((void *)s);
	return (NULL);
}
