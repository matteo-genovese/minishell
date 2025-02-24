/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:31:42 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/24 10:00:08 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count(char *s, char c, size_t *offset)
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
		return (ft_substr(s, i + count(s, '0', off), j - i - count(s, '0', off)));
	while (s[j] && s[j] != ' ' && !is_exotic_char(s[j]))
	{
		if (s[j] == '\'' || s[j] == '"')
		{
			j = handle_quotes(s, sep, j);
			if (!j)
				return (NULL);
		}
		else
			j++;
	}
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
	while (input && *input == ' ')
		input++;
	if (input && !pre_prompt_check(input))
		return (init_error_handler(input[0]));
	while (i < ft_strlen(input))
	{
		offset = 0;
		token = next_token(input + i, &offset);
		if (!token)
			return (parser_handle_token_error(tokens, quotes));
		i += ft_strlen(token) + offset;
		while (input[i] && input[i] == ' ')
			i++;
		ft_lstadd_back(&quotes, ft_lstnew(token_has_quotes(token)));
		token = preprocessed(token, tools, last_exit_code);
		ft_lstadd_back(&tokens, ft_lstnew(token));
	}
	return (parser_build_result(tokens, quotes));
}
