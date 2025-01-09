/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:31:51 by mgenoves          #+#    #+#             */
/*   Updated: 2025/01/09 22:32:40 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
