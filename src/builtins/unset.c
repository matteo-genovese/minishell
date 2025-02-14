/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:00:21 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/17 18:44:11 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **targets, char ***envp)
{
	int	i;

	i = 1;
	while (targets[i])
	{
		unset_target(targets[i], envp);
		i++;
	}
}

void	unset_target(char *target, char ***envp)
{
	int		i;
	int		j;
	int		len;
	char	**new_envp;

	len = 0;
	i = -1;
	j = 0;
	while ((*envp)[++i])
		if (ft_strncmp(target, (*envp)[i], ft_strlen(target))
			|| !((*envp)[i][ft_strlen(target)] == '='))
			len++;
	new_envp = (char **)malloc(sizeof(char *) * (len + 1));
	new_envp[len] = NULL;
	i = -1;
	while ((*envp)[++i])
	{
		if (ft_strncmp(target, (*envp)[i], ft_strlen(target))
			|| !((*envp)[i][ft_strlen(target)] == '='))
			new_envp[j++] = ft_strdup((*envp)[i]);
		free((*envp)[i]);
	}
	free(*envp);
	*envp = new_envp;
}
