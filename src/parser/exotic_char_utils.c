/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exotic_char_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:58:44 by starry            #+#    #+#             */
/*   Updated: 2025/02/21 11:12:26 by fde-sist         ###   ########.fr       */
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

static bool	double_char_handler(char *sub, char *to_free)
{
	if (sub[1])
		printf("minishell: syntax error near unexpected token '%c%c'\n", *sub,
			sub[1]);
	printf("minishell: syntax error near unexpected token '%c'\n", *sub);
	free(to_free);
	return (false);
}

static bool	exceeded_count_handler(char *sub, char last_char, char *to_free)
{
	if (sub[1] && sub[1] == last_char)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(last_char, 2);
		ft_putchar_fd(last_char, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(last_char, 2);
		ft_putstr_fd("'\n", 2);
	}
	free(to_free);
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
			return (double_char_handler(sub, temp));
		if (same_char_count > 2)
			return (exceeded_count_handler(sub, last_char, temp));
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
