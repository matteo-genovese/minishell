/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_preprocessing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:00:08 by starry            #+#    #+#             */
/*   Updated: 2025/02/20 13:34:13 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_sep_index(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	if (s[0] && s[0] == '$')
		i++;
	while (s[i])
	{
		if (is_parser_separator(s[i]) || s[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

static char	*handle_non_existent(char *s, char *dest, size_t *i)
{
	size_t	sep_indx;
	char	*out;

	sep_indx = get_sep_index(s);
	if (s[1] && s[2] && ft_isdigit(s[1]))
	{
		out = ft_substr(s, 2, sep_indx - 2);
		*i += sep_indx;
		return (joinfree(dest, out));
	}
	*i += sep_indx;
	return (ft_strdup(""));
}

char	*env_processing(char *s, char *dest, size_t *i, t_tools *tools)
{
	char	*out;
	char	*env;
	size_t	sep_indx;
	char	*temp;

	sep_indx = get_sep_index(s);
	if (sep_indx == 1)
	{
		*i += 1;
		return (join_char(dest, '$'));
	}
	temp = ft_substr(s, 1, sep_indx - 1);
	env = get_value_envp(temp, tools->envp);
	if (!env)
	{
		free(temp);
		return (handle_non_existent(s, dest, i));
	}
	free(temp);
	out = joinfree(dest, ft_strdup(env));
	*i += sep_indx;
	return (out);
}
