/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:03:43 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/14 16:33:33 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **command)
{
	int	i;
	int	n_flag;

	n_flag = (command[1] && !ft_strncmp(command[1], "-n", 2));
	i = n_flag;
	while (command[++i])
	{
		ft_putstr_fd(command[i], STDOUT_FILENO);
		if (command[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
