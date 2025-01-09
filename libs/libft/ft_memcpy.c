/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:53:37 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/15 11:30:35 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t lenght)
{
	char		*aux_dest;
	const char	*aux_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	aux_dest = dest;
	aux_src = src;
	while (lenght--)
		*(aux_dest + lenght) = *(aux_src + lenght);
	return (dest);
}
