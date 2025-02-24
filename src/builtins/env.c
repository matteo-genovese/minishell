/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:50:02 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/24 12:00:21 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** outputs to standard output the environment variables
** @param envp: the environment variables
*/
int	env(char **envp, char **command)
{
	int	i;

	if (command[1])
	{
		ft_putstr_fd("minishell: env: too many args", 2);
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			ft_putstr_fd(envp[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
