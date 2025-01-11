/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:44:25 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/11 18:39:52 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*Returns the found path+command, NULL if command is not found*/
char	*set_command(char *command, char **paths)
{
	char	*path_to_command;
	int		i;
	char	*output;

	i = -1;
	output = NULL;
	while (paths[++i])
	{
		path_to_command = ft_strjoin_fw(paths[i], command);
		if (!access(path_to_command, F_OK | X_OK) && !output)
			output = ft_strjoin(paths[i], command);
		free(path_to_command);
	}
	return (output);
}

int	is_command(char *command, char **paths)
{
	char	*path_to_command;
	int		output;
	int		i;

	i = -1;
	output = EXIT_FAILURE;
	while (paths[++i])
	{
		path_to_command = ft_strjoin(paths[i], command);
		if (!access(path_to_command, F_OK | X_OK) && output)
			output = EXIT_SUCCESS;
		free(path_to_command);
	}
	return (output);
}
