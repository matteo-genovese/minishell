/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:49:47 by starry            #+#    #+#             */
/*   Updated: 2025/02/15 00:21:48 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	super_free(char *dest, char *env)
{
	free(dest);
	free(env);
}

char	*env_processing(char *s, char *dest, size_t *i, t_tools *tools)
{
	char	*env;
	char	*out;
	size_t	j;
	char	*val;

	j = 0;
	while (s[*i + j] && !is_parser_separator(s[*i + j]))
		j++;
	env = ft_substr(s, *i, j);
	val = get_value_envp(env + 1, tools->envp);
	if (!val)
	{
		if (ft_strlen(s) == 2)
			out = ft_strjoin(dest, "");
		else
			out = ft_strjoin(dest, s + 2);
		super_free(dest, env);
		*i += j;
		return (out);
	}
	out = ft_strjoin(dest, val);
	super_free(dest, env);
	*i += j;
	return (out);
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
	out = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '"')
			handle_quotes(&inside_2quotes, &i);
		else if (s[i] == '\'' && !inside_2quotes)
			out = hadle_single_quotes(s, out, &i);
		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
		{
			out = joinfree(out, ft_itoa(last_exit_code));
			i += 2;
		}
		else if (s[i] == '$')
			out = env_processing(s, out, &i, tools);
		else
			out = join_char(out, s[i++]);
	}
	free(s);
	return (out);
}
