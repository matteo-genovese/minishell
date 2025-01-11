/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:48:54 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/11 18:49:03 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	execute_command(char **envp, char **command)
{
	char	**paths;
	char	*commnad_with_path;
	pid_t	pid;

	paths = find_path(envp);
	if (is_command(command[0], paths))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (is_command(command[0], paths) || !is_special_command(command))
	{
		free_string_array(paths);
		return (EXIT_FAILURE);
	}
	commnad_with_path = set_command(command[0], paths);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execve(commnad_with_path, command, envp);
	wait(0);
	free(commnad_with_path);
	free_string_array(paths);
	return (EXIT_SUCCESS);
}

int	is_special_command(char **command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i])
	{
		while (command[i][j])
		{
			if (command[i][j] == '|' || command[i][j] == '<'
				|| command[i][j] == '>')
				return (EXIT_SUCCESS);
			j++;
		}
		j = 0;
		i++;
	}
	return (EXIT_FAILURE);
}
