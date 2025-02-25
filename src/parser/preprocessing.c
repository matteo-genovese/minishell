/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:49:47 by starry            #+#    #+#             */
/*   Updated: 2025/02/25 16:26:00 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(bool *inside_2quotes, size_t *i)
{
	*inside_2quotes = !*inside_2quotes;
	(*i)++;
}

static char	*hadle_single_quotes(char *s, char *out, size_t *i)
{
	*i += 1;
	while (s[*i])
	{
		if (s[*i] == '\'')
		{
			*i += 1;
			return (out);
		}
		out = join_char(out, s[*i]);
		*i += 1;
	}
	return (NULL);
}

char	*preprocessed(char *s, t_tools *tools, int last_exit_code)
{
	char	*out;
	size_t	i;
	bool	inside_2quotes;

	i = 0;
	inside_2quotes = false;
	out = ft_strdup("");
	while (s && s[i])
	{
		if (s[i] == '"')
			handle_quotes(&inside_2quotes, &i);
		else if (s[i] == '\'' && !inside_2quotes)
			out = hadle_single_quotes(s, out, &i);
		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
		{
			out = joinfree(out, ft_itoa(last_exit_code), true, true);
			i += 2;
		}
		else if (s[i] == '$')
			out = env_processing(s + i, out, &i, tools);
		else
			out = join_char(out, s[i++]);
	}
	free(s);
	if (out[0] == '\0')
	{
		free(out);
		return (NULL);
	}
	return (out);
}
