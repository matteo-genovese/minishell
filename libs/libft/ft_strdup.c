/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:01:51 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/25 15:47:48 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_string;
	char	*start;

	if (!s)
		return (NULL);
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
