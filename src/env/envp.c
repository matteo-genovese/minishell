/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:31:51 by mgenoves          #+#    #+#             */
/*   Updated: 2025/01/17 18:44:30 by starry           ###   ########.fr       */
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

char	*get_value_envp(char *name, char **envp)
{
	int		i;
	char	*value;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(name, envp[i], ft_strlen(name)))
		{
			value = ft_strchr(envp[i], '=') + 1;
			return (value);
		}
	}
	return (NULL);
}
