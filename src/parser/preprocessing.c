/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:49:47 by starry            #+#    #+#             */
/*   Updated: 2025/02/25 18:09:45 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_tilde(char *s, t_tools *tools, size_t *i)
{
	if (ft_strlen(s) > 1 && s[1] == '/')
	{
		*i += 2;
		return (ft_strjoin(get_value_envp("HOME", tools->envp), "/"));
	}
	else if (ft_strlen(s) == 1)
	{
		*i += 1;
		return (ft_strdup(get_value_envp("HOME", tools->envp)));
	}
	else
	{
		*i += 1;
		return (ft_strdup("~"));
	}
}

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
	if (s && s[i] == '~')
		out = expand_tilde(s, tools, &i);
	else
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
