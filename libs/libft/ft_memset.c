/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:51:01 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/07 12:53:39 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *a, int c, size_t lenght)
{
	char	*p;

	p = (char *)a;
	while (lenght--)
		*(p + lenght) = c;
	return (a);
}
