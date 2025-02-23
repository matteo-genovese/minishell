/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:31:51 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/23 22:48:49 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_envp(t_tools *tools, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	tools->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tools->envp)
		exit(EXIT_FAILURE);
	i = 0;
	while (envp[i])
	{
		tools->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	tools->envp[i] = NULL;
}

static int	get_index_of(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

size_t	max_length(size_t l, size_t l2)
{
	if (l > l2)
		return (l);
	return (l2);
}

char	*get_value_envp(char *name, char **envp)
{
	int		i;
	char	*value;
	size_t	biggest_length;
	int		indx;

	i = 0;
	while (envp[i])
	{
		indx = get_index_of(envp[i], '=');
		biggest_length = max_length(ft_strlen(name), ft_strlen(envp[i]));
		if (indx >= 0 && ft_strncmp(name, envp[i], biggest_length) == 0)
		{
			value = envp[i] + indx + 1;
			return (value);
		}
		i++;
	}
	return (NULL);
}
