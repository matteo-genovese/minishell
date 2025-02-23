/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exotic_char_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:58:44 by starry            #+#    #+#             */
/*   Updated: 2025/02/23 22:35:17 by starry           ###   ########.fr       */
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

bool	is_valid_exotic_sequence(char *s, int length)
{
	char	*sub;
	char	*temp;
	char	last_char;
	int		same_char_count;

	if (!s)
		return (true);
	temp = ft_substr(s, 0, length);
	sub = temp + 1;
	last_char = s[0];
	same_char_count = 1;
	while (*sub)
	{
		if (*sub == last_char)
			same_char_count++;
		else
			return (diff_char_handler(sub, temp));
		if (same_char_count > 2)
			return (exceeded_count_handler(sub, last_char, temp));
		sub++;
	}
	free(temp);
	return (true);
}

int	handle_redirect(char *s, int j)
{
	size_t	digits;
	int		j_prev;

	j_prev = j;
	digits = 0;
	while (ft_isdigit(s[j + digits]))
		digits++;
	if (digits > 10)
		digits = 0;
	while (s[j + digits] && (s[j + digits] == '>' || s[j + digits] == '<'))
		j++;
	if (j > 0 && !is_valid_exotic_sequence(s + digits, j))
		return (-1);
	if (j_prev == j)
		return (0);
	return (j + digits);
}
