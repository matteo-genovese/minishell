/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:03:43 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/21 19:10:00 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** echo builtin, -n flag is handled
*/
int	echo(char **command)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	while (!ft_strncmp(command[++i], "-n", 3))
		n_flag = 1;
	while (command[i])
	{
		ft_putstr_fd(command[i], STDOUT_FILENO);
		if (command[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
