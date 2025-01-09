/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_fw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:40:31 by fde-sist          #+#    #+#             */
/*   Updated: 2024/09/21 20:49:04 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates and joins first string to the first word of the second*/
char	*ft_strjoin_fw(char const *s1, char const *s2)
{
	char	*start;
	char	*joined;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_wlen(s2) + 1;
	joined = (char *) malloc((len) * sizeof(char));
	start = joined;
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, ft_strlen(s1) + 1);
	joined += ft_strlen(s1);
	ft_strlcpy(joined, s2, ft_wlen(s2) + 1);
	return (start);
}
