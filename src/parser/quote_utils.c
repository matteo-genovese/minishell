/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:41:49 by starry            #+#    #+#             */
/*   Updated: 2025/01/21 19:45:29 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

/**
 * @param s: string
 *
 * @return 0 no quotes, 1 single quotes, 2 double quotes
 */
int	has_quotes(char *s)
{
	size_t	s_len;

	if (!s)
		return (false);
	s_len = ft_strlen(s);
	if (s[0] == '\'' && s[s_len - 1] == '\'')
		return (1);
	if (s[0] == '"' && s[s_len - 1] == '"')
		return (2);
	return (0);
}

char	*trim_quotes(char *s)
{
	char	*out;
	char	quote[2];

	if (!s)
		return (NULL);
	if (has_quotes(s) == 0)
		return (s);
	quote[0] = s[0];
	quote[1] = '\0';
	out = ft_strtrim(s, quote);
	if (!out)
		return (NULL);
	free(s);
	return (out);
}

inline bool	is_parser_separator(char c)
{
	return (c == ' ' || c == '\'' || c == '"');
}
