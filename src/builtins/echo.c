/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:03:43 by mgenoves          #+#    #+#             */
/*   Updated: 2025/01/09 22:05:33 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	echo(char *input)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	if (ft_strncmp(input, "echo", 4) != 0)
		return (0);
	i += 4;
	while (input[i] == ' ')
		i++;
	if (ft_strncmp(input + i, "-n", 2) == 0)
	{
		n_flag = 1;
		i += 2;
		while (input[i] == ' ')
			i++;
	}
	ft_putstr_fd(input + i, 1);
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (1);
}
