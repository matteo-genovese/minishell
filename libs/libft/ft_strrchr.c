/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:04:17 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/16 16:22:33 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_found;

	last_found = NULL;
	while (*s)
	{
		if (*s == (char) c)
			last_found = (char *)s;
		s++;
	}
	if (*s == (char) c)
		last_found = (char *)s;
	return (last_found);
}
