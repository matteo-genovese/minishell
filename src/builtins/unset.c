/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:00:21 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/10 14:21:20 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	unset(char *target, char ***envp)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while ((*envp)[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * i);
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
