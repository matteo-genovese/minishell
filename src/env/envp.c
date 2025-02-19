/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:31:51 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/18 16:16:15 by starry           ###   ########.fr       */
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

char	*get_value_envp(char *name, char **envp)
{
	int		i;
	char	*value;
	int		indx;

	i = 0;
	while (envp[i])
	{
		indx = get_index_of(envp[i], '=');
		if (indx >= 0 && ft_strncmp(name, envp[i], indx) == 0)
		{
			value = envp[i] + indx + 1;
			return (value);
		}
		i++;
	}
	return (NULL);
}
