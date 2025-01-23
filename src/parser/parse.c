/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:31:42 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/23 23:56:26 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

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

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	j = i;
	while (s[j] == '\'' || s[j] == '"')
	{
		sep = s[j];
		j++;
		while (s[j] != sep)
		{
			if (!s[j])
				return (NULL);
			j++;
		}
		j++;
	}
	while (s[j] && s[j] != ' ')
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
			printf("minishell: error: unmatched quotes\n");
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
