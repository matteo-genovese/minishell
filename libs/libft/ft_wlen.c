/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wlen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:42:18 by fde-sist          #+#    #+#             */
/*   Updated: 2024/09/23 00:12:25 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns the length of the first word delimited by a space*/
size_t	ft_wlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}
