/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exotic_char_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:58:44 by starry            #+#    #+#             */
/*   Updated: 2025/02/13 16:58:31 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_exotic_char(char c)
{
	char	*exotic_chars;

	exotic_chars = "<>|";
	while (*exotic_chars)
	{
		if (c == *exotic_chars)
			return (true);
		exotic_chars++;
	}
	return (false);
}

size_t	handle_redirect(char *s, size_t j)
{
	char	read;
	size_t	digits;

	digits = 0;
	while (ft_isdigit(s[j + digits]))
		digits++;
	read = 0;
	if (s[j + digits] && (s[j + digits] == '>' || s[j + digits] == '<'))
	{
		read = s[j + digits];
		while (s[j + digits] == read)
			j++;
	}
	return (j + digits);
}
