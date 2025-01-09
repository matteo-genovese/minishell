/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:31:07 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/19 15:24:21 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_increment(size_t *i, size_t *j)
{
	(*i)++;
	(*j)++;
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!len && !big) || !(*little))
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (big[i] == little[j] && i < len && big[i] && little[j])
			ft_increment(&i, &j);
		if (little[j] == '\0')
			return ((char *)(big + (i - j)));
		else
		{
			i = i - j;
			j = 0;
		}
		i++;
	}
	if (big[i] == little[0] && i < len)
		return ((char *) big);
	return (NULL);
}
