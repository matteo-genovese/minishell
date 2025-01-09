/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:28:27 by mgenoves          #+#    #+#             */
/*   Updated: 2025/01/09 21:28:46 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
