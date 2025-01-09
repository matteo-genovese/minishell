/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:03:01 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/20 22:16:59 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			i++;
			while (*s != c && *s)
				s++;
		}
	}
	return (i);
}

size_t	pointer_dist(char const *from, char const *to)
{
	size_t	i;

	i = 0;
	while (from + i != to)
		i++;
	return (i);
}

int	set_list(char *start, char **list, char c, const char *s)
{
	while (*s == c)
		s++;
	while (*s)
	{
		start = (char *)s;
		while (*s != c && *s)
			s++;
		*list = ft_substr(start, 0, pointer_dist(start, s));
		if (!(*list))
			return (1);
		list++;
		while (*s == c && *s)
			s++;
	}
	*list = NULL;
	return (0);
}

int	free_list(char *start, char **list, char c, const char *s)
{
	size_t	i;
	size_t	words;

	words = count_words(s, c);
	i = 0;
	if (set_list(start, list, c, s))
	{
		while (i < words)
		{
			free(list[i]);
			i++;
		}
		free(list);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	char	*start;
	char	**list_start;

	if (!s)
		return (NULL);
	start = (char *)s;
	while (*(s) == c && *s)
		s++;
	if (*s == 0)
	{
		list = (char **)malloc(sizeof(char *));
		if (!list)
			return (NULL);
		*list = NULL;
		return (list);
	}
	s = start;
	list = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	list_start = list;
	if (free_list(start, list, c, s))
		return (NULL);
	return (list_start);
}
