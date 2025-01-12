/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:37:03 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/12 14:15:42 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*Returns a list of the paths included in the PATH enviroment variable*/
char	**find_path(char **envp, int index)
{
	char	**output;
	char	*aux;
	int		path_index;

	while (envp[index] != NULL)
	{
		if (!ft_strncmp(envp[index], "PATH=", 5))
			break ;
		index++;
	}
	if (envp[index] == NULL)
		return (NULL);
	envp[index] += 5;
	path_index = index;
	output = ft_split(envp[index], ':');
	index = 0;
	while (output[index])
	{
		aux = ft_strjoin(output[index], "/");
		free(output[index]);
		output[index++] = aux;
	}
	envp[path_index] -= 5;
	return (output);
}
