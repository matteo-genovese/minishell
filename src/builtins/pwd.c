/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:28:27 by mgenoves          #+#    #+#             */
/*   Updated: 2025/01/17 18:44:07 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_putstr_fd("Error: pwd: cannot get current directory\n", 2);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(path, 1);
	free(path);
	return (EXIT_SUCCESS);
}
