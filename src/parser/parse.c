/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:31:42 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/18 15:38:42 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

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
	if (s[j] == '\'' || s[j] == '"')
	{
		sep = s[j];
		j++;
		while (s[j] && s[j] != sep)
			j++;
		j++;
	}
	else
	{
		while (s[j] && s[j] != ' ')
			j++;
	}
	token = ft_substr(s, i, j - i);
	return (token);
}

/**
 * @note heap allocation
 * @param input: bash prompt
 * @param tools: the tools struct
 * @param last_exit_code
 *
 * @return preprocessed input
 */
char	**parse(char *input, t_tools *tools, int last_exit_code)
{
	size_t			i;
	struct s_list	*tokens;
	char			*temp;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		printf("input: %s\n", input);
		temp = next_token(input + i);
		i += ft_strlen(temp) + 1;
		printf("token (%zu): %s\n", strlen(temp), temp);
		if (has_quotes(temp) != 1)
		{
			temp = trim_quotes(temp);
			temp = preprocessed(temp, tools, last_exit_code);
		}
		else
			temp = trim_quotes(temp);
		printf("processed: %s\n", temp);
		ft_lstadd_back(&tokens, ft_lstnew(temp));
	}
	return (stringarr_from_list(tokens));
}
