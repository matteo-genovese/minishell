/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exotic_char_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:58:44 by starry            #+#    #+#             */
/*   Updated: 2025/02/19 19:57:13 by starry           ###   ########.fr       */
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
	char	last_char;
	int		same_char_count;

	if (!s)
		return (true);
	sub = ft_substr(s, 0, length);
	printf("checking: %s\n", sub);
	last_char = s[0];
	same_char_count = 1;
	sub++;
	while (*sub)
	{
		if (*sub == last_char)
			same_char_count++;
		else
		{
			printf("minishell: syntax error near unexpected token '%c'\n",
				*sub);
			return (false);
		}
		if (same_char_count > 2)
		{
			if (sub[1] && sub[1] == last_char)
				printf("minishell: syntax error near unexpected token '%c%c'\n",
					last_char, last_char);
			else
				printf("minishell: syntax error near unexpected token '%c'\n",
					last_char);
			return (false);
		}
		sub++;
	}
	return (true);
}

int	handle_redirect(char *s, int j)
{
	size_t	digits;

	digits = 0;
	while (ft_isdigit(s[j + digits]))
		digits++;
	if (digits > 10)
		digits = 0;
	while (s[j + digits] && (s[j + digits] == '>' || s[j + digits] == '<'))
		j++;
	if (j > 0 && !is_valid_exotic_sequence(s + digits, j))
		return (-1);
	return (j + digits);
}
