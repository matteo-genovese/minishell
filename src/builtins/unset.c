/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:00:21 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/20 22:18:37 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** @param targets: the targets to unset
** @param envp: the environment variables address
*/
int	unset(char **targets, char ***envp)
{
	int	i;

	i = 1;
	while (targets[i])
	{
		unset_target(targets[i], envp);
		i++;
	}
	return (0);
}

/*
** @param target: the target to unset
** @param envp: the environment variables address
** @return void
*/
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
