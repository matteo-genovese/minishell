/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:41:37 by starry            #+#    #+#             */
/*   Updated: 2025/02/23 20:34:29 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

char	*join_char(char *s, char c)
{
	char	*out;

	if (!s)
		return (NULL);
	out = ft_calloc(ft_strlen(s) + 2, sizeof(char));
	ft_strlcat(out, s, ft_strlen(s) + 1);
	out[ft_strlen(s)] = c;
	free(s);
	return (out);
}

/**
 * @param s: string
 * @param s2: string
 * @warning heap allocation
 * @warning frees s and s2
 *
 * @return joined string
 */
char	*joinfree(char *s, char *s2)
{
	char	*out;

	out = ft_calloc(ft_strlen(s) + ft_strlen(s2) + 1, sizeof(char));
	ft_strlcat(out, s, ft_strlen(s) + 1);
	ft_strlcat(out, s2, ft_strlen(s) + ft_strlen(s2) + 1);
	free(s);
	free(s2);
	return (out);
}

static void	helper(char **out, t_list *head, t_list *head_q, size_t i)
{
	out[i] = NULL;
	ft_lstclear(&head, &free);
	ft_lstclear(&head_q, &free);
}

/**
 * @note trims
 */
t_parser_result	*parser_build_result(struct s_list *l, struct s_list *quotes)
{
	struct s_list	*head;
	struct s_list	*head_q;
	char			**out;
	size_t			i;
	t_parser_result	*result;

	if (!l)
		return (NULL);
	out = ft_calloc(ft_lstsize(l) + 1, sizeof(char *));
	result = parser_result_init(out, ft_calloc(ft_lstsize(l), sizeof(bool)));
	i = 0;
	if (l && l->content && !ft_strncmp((char *)l->content, "", 1))
	{
		l = l->next;
		quotes = quotes->next;
	}
	head = l;
	head_q = quotes;
	while (l)
	{
		out[i] = ft_strdup(l->content);
		result->quotes[i] = ((bool *)quotes->content)[0];
		l = l->next;
		quotes = quotes->next;
		i++;
	}
	helper(out, head, head_q, i);
	return (result);
}

void	*parser_handle_token_error(t_list *tokens)
{
	ft_lstclear(&tokens, &free);
	return (NULL);
}
