/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:44:25 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/11 19:10:41 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*Returns the found path+command, NULL if command is not found*/
char	*set_command(char *command, char **paths, char **envp)
{
	char	*path_to_command;
	int		i;
	char	*output;

	if (is_non_path(command))
		return (non_path_command(command, envp));
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

char	*non_path_command(char *command, char **envp)
{
	int		i;
	char	*aux;

	i = 0;
	if (command[0] == '~')
	{
		command[0] = '/';
		while (ft_strncmp(envp[i], "HOME=", 5))
			i++;
		aux = ft_strjoin(ft_strchr(envp[i], '=') + 1, command);
		return (aux);
	}
	if (command[0] == '.')
	{
		while (ft_strncmp(envp[i], "PWD=", 4))
			i++;
		aux = ft_strjoin(ft_strchr(envp[i], '=') + 1, command + 1);
		return (aux);
	}
	return (command);
}

int	is_non_path(char *command)
{
	return (command[0] == '.' || command[0] == '/' || command[0] == '~');
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
