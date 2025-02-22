/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:31:42 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/21 17:13:12 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ct(char *s, char c, size_t *offset)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == c)
		i++;
	*offset = i;
	return (i);
}

static int	handle_quotes(char *s, char sep, size_t j)
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
static char	*next_token(char *s, size_t *off)
{
	int		i;
	int		j;
	char	sep;

	sep = 0;
	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '|')
		return (ft_strdup("|"));
	j = handle_redirect(s, i);
	if (j == -1)
		return (NULL);
	if (j > i)
		return (ft_substr(s, i + ct(s, '0', off), j - i - ct(s, '0', off)));
	if (s[j] == '\'' || s[j] == '"')
	{
		j = handle_quotes(s, sep, j);
		if (!j)
			return (NULL);
	}
	while (s[j] && s[j] != ' ' && !is_exotic_char(s[j]))
		j++;
	return (ft_substr(s, i, j - i));
}

/**
 * @note heap allocation
 * @param input: bash prompt
 * @param tools: the tools struct
 * @param last_exit_code
 * @warning hidden bug
 *
 * @return preprocessed input in t_parser_result *
 */
t_parser_result	*parse(char *input, t_tools *tools, int last_exit_code)
{
	struct s_list	*tokens;
	char			*token;
	size_t			offset;
	size_t			i;
	struct s_list	*quotes;

	i = 0;
	tokens = NULL;
	quotes = NULL;
	if (input && is_exotic_char(input[0]))
		return (init_error_handler(input[0]));
	while (i < ft_strlen(input))
	{
		offset = 0;
		token = next_token(input + i, &offset);
		if (!token)
			return (parser_handle_token_error(tokens));
		i += ft_strlen(token) + offset;
		while (input[i] && input[i] == ' ')
			i++;
		ft_lstadd_back(&quotes, ft_lstnew(token_has_quotes(token)));
		token = preprocessed(token, tools, last_exit_code);
		ft_lstadd_back(&tokens, ft_lstnew(token));
	}
	return (parser_build_result(tokens, quotes));
}
