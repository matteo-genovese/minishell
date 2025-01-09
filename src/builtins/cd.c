/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:09:17 by mgenoves          #+#    #+#             */
/*   Updated: 2025/01/09 22:18:38 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	cd(char *path)
{
	int i;

	i = 0;
	while(path[i] == ' ')
		i++;
	if (chdir(path + i) == -1)
	{
		ft_putstr_fd("Error: cd: ", 2);
		ft_putstr_fd(path + i, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
