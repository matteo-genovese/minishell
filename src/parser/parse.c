/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:31:42 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/14 17:58:32 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <assert.h>
#include <stdbool.h>

static size_t	handle_quotes(char *s, char sep, size_t j)
{
	while (s[j] == '\'' || s[j] == '"')
	{
		sep = s[j];
		j++;
		while (s[j] != sep)
		{
			if (!s[j])
			{
				ft_putstr_fd("unmatched quote\n", STDERR_FILENO);
				return (0);
			}
			j++;
		}
		j++;
	}
	return (j);
}

/**
 * @note if does't match a separator before \0 returns NULL
 *
 * @return next token from pointer
 */
static char	*next_token(char *s)
{
	size_t	i;
	size_t	j;
	char	sep;
	char	*token;

	sep = 0;
	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '|')
		return (ft_strdup("|"));
	j = handle_redirect(s, i);
	if (j > i)
		return (ft_substr(s, i, j - i));
	if (s[j] == '\'' || s[j] == '"')
	{
		j = handle_quotes(s, sep, j);
		if (!j)
			return (NULL);
	}
	while (s[j] && s[j] != ' ' && !is_exotic_char(s[j]))
		j++;
	token = ft_substr(s, i, j - i);
	return (token);
}

/**
 * @note heap allocation
 * @param input: bash prompt
 * @param tools: the tools struct
 * @param last_exit_code
 * @warning hidden bug
 *
 * @return preprocessed input
 */
char	**parse(char *input, t_tools *tools, int last_exit_code)
{
	size_t			i;
	struct s_list	*tokens;
	char			*temp;
	size_t			len;

	i = 0;
	tokens = NULL;
	len = ft_strlen(input);
	while (i < len)
	{
		temp = next_token(input + i);
		if (!temp)
		{
			ft_lstclear(&tokens, &free);
			return (NULL);
		}
		i += ft_strlen(temp);
		while (input[i] && input[i] == ' ')
			i++;
		temp = preprocessed(temp, tools, last_exit_code);
		ft_lstadd_back(&tokens, ft_lstnew(temp));
	}
	return (stringarr_from_list(tokens));
}
