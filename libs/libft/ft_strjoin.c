/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:37:22 by fde-sist          #+#    #+#             */
/*   Updated: 2024/10/17 12:20:25 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*start;
	char	*joined;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *) malloc((len) * sizeof(char));
	start = joined;
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, ft_strlen(s1) + 1);
	joined += ft_strlen(s1);
	ft_strlcpy(joined, s2, ft_strlen(s2) + 1);
	return (start);
}
