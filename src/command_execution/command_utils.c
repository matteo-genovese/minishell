/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:44:25 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/16 19:30:51 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*Returns 1 if command is a path 0 otherwise*/
int	is_path(char *command)
{
	return (command[0] == '.' || command[0] == '/' || command[0] == '~');
}

/*Returns 1 if command is found in PATH 0 otherwise*/
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

/*Returns lenght of string array*/
int	ft_n_args(char **command)
{
	int	i;
	int	n_args;

	n_args = 0;
	while (command[n_args])
		n_args++;
	i = 0;
	while (command[1] && command[1][i] == ' ')
		i++;
	return (n_args);
}

/*Returns 1 if passed path is a directory 0 otherwise*/
int	is_directory(const char *path)
{
	struct stat	s_path_stat;

	if (access(path, F_OK) != 0)
		return (0);
	if (stat(path, &s_path_stat) != 0)
		return (0);
	return (S_ISDIR(s_path_stat.st_mode));
}
