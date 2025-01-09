/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:18:44 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/15 11:28:03 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*aux_dest;
	char	*aux_src;
	size_t	i;

	aux_dest = (char *)dest;
	aux_src = (char *)src;
	if (n == 0 || (!dest && !src))
		return (dest);
	if (aux_dest > aux_src)
	{
		while (n--)
			aux_dest[n] = aux_src[n];
	}
	else
	{
		i = -1;
		while (++i < n)
			aux_dest[i] = aux_src[i];
	}
	return (dest);
}
