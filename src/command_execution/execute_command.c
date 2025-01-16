/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:48:54 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/16 22:27:12 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*Outputs debug on screen*/
int	command_not_found(char **command, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command[0], 2);
	if (flag == 1)
	{
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
	else if (flag == 2)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	if (command[0][0] == '/' || command[0][0] == '.')
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found...\n", 2);
	return (127);
}

/*Returns bash-like if command is invalid 0 otherwise*/
int	invalid_command(char **command, char *command_with_path, char ***paths)
{
	int	output;

	output = 0;
	if (command_with_path == NULL || access(command_with_path, F_OK | X_OK))
	{
		if (command_with_path && access(command_with_path, X_OK)
			&& !access(command_with_path, F_OK))
			output = command_not_found(command, 2);
		else
			output = command_not_found(command, 0);
		free_string_array(*paths);
		free(command_with_path);
		return (output);
	}
	if (is_directory(command_with_path))
	{
		output = command_not_found(command, 1);
		free_string_array(*paths);
		free(command_with_path);
		return (output);
	}
	return (output);
}

/*Takes command with args and flags, envp, and exectutes it*/
int	execute_command(char **envp, char **command)
{
	char	**paths;
	char	*command_with_path;
	pid_t	pid;
	int		exit_value;

	paths = find_path(envp, 0);
	if (!is_special_command(command))
		return (printf("we dont do that here\n"));
	command_with_path = set_command(command, paths, envp);
	exit_value = invalid_command(command, command_with_path, &paths);
	if (exit_value)
		return (exit_value);
	free(command[0]);
	command[0] = command_with_path;
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: pipe error\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(command_with_path, command, envp);
	}
	free_string_array(paths);
	return (father_process(pid));
}

/*Checks if child process exited and handles SIGINT*/
int	father_process(int pid)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		ft_putstr_fd("\n", 2);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	signal(SIGINT, signal_handler);
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (WEXITSTATUS(status));
}

/*Temporary function to handle pipes and redirection*/
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
