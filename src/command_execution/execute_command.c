/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:48:54 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/16 12:41:13 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	command_not_found(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int	execute_command(char **envp, char **command)
{
	char	**paths;
	char	*commnad_with_path;
	pid_t	pid;

	paths = find_path(envp, 0);
	if (is_command(command[0], paths) && !is_non_path(command[0]))
		command_not_found(command[0]);
	if ((is_command(command[0], paths) || !is_special_command(command))
		&& !is_non_path(command[0]))
	{
		free_string_array(paths);
		return (EXIT_FAILURE);
	}
	commnad_with_path = set_command(command, paths, envp);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execve(commnad_with_path, command, envp);
	father_process(pid);
	free(commnad_with_path);
	free_string_array(paths);
	return (EXIT_SUCCESS);
}

void	father_process(int pid)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	signal(SIGINT, signal_handler);
}

int	is_special_command(char **command)
{
	int	i;
	int	j;

	i = 0;
	while (command[i])
	{
		j = 0;
		while (command[i][j])
		{
			if (command[i][j] == '|' || command[i][j] == '<'
				|| command[i][j] == '>')
				return (EXIT_SUCCESS);
			j++;
		}
		i++;
	}
	return (EXIT_FAILURE);
}
