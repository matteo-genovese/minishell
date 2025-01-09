/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:01:51 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/18 18:13:32 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_string;
	char	*start;

	new_string = (char *)malloc(ft_strlen(s) + 1);
	if (!new_string)
		return (NULL);
	start = new_string;
	while (*s)
	{
		*new_string = *s;
		new_string++;
		s++;
	}
	*new_string = *s;
	return (start);
}
