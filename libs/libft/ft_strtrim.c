/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:21:02 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/20 18:04:08 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	is_in_set(const char test, char const *set)
{
	while (*set)
	{
		if (*set == test)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (is_in_set(s1[start], set))
		start++;
	if (start > end)
		return (ft_strdup(""));
	while (is_in_set(s1[end], set))
		--end;
	str = ft_substr(s1, start, end - start + 1);
	if (!str)
		return (NULL);
	return (str);
}
