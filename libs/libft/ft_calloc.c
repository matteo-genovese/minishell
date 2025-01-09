/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:21:11 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/17 18:40:28 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*output;
	size_t	i;

	i = 0;
	output = (void *)malloc(nmeb * size);
	if (!output)
		return (NULL);
	while (i != size * nmeb)
	{
		((char *)output)[i] = 0;
		i++;
	}
	return (output);
}
