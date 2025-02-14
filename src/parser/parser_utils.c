/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:41:37 by starry            #+#    #+#             */
/*   Updated: 2025/01/22 13:29:21 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

char	*join_char(char *s, char c)
{
	char	*out;

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

char	**stringarr_from_list(struct s_list *l)
{
	struct s_list	*head;
	char			**out;
	size_t			i;

	if (!l)
		return (NULL);
	out = ft_calloc(ft_lstsize(l) + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	head = l;
	while (l)
	{
		out[i] = ft_strdup(l->content);
		l = l->next;
		i++;
	}
	out[i] = NULL;
	ft_lstclear(&head, &free);
	return (out);
}
