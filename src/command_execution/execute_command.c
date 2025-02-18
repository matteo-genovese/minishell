/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:48:54 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/18 12:26:43 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putstr_fd(": command not found\n", 2);
	return (127);
}

/*Returns bash-like if command is invalid 0 otherwise*/
int	invalid_command(char **command, char *command_with_path)
{
	int	output;

	output = 0;
	if (is_builtin(command[0]))
		return (0);
	if (is_directory(command[0]) || is_directory(command_with_path))
	{
		output = command_not_found(command, 1);
		free(command_with_path);
		return (output);
	}
	if (command_with_path == NULL || access(command_with_path, F_OK | X_OK))
	{
		if (command_with_path && access(command_with_path, X_OK)
			&& !access(command_with_path, F_OK))
			output = command_not_found(command, 2);
		else
			output = command_not_found(command, 0);
		free(command_with_path);
		return (output);
	}
	return (output);
}

/*Takes command with args and flags, envp, and exectutes it*/
int	execute_command(t_tools *tools, char **command)
{
	pid_t			pid;
	int				pipefd[2];
	int				last_exit;
	int				std_in_fd[2];

	std_in_fd[0] = dup(STDIN_FILENO);
	std_in_fd[1] = dup(STDOUT_FILENO);
	while (*command)
	{
		if (pipe(pipefd) == -1)
			ft_error("pipe", command);
		pid = fork();
		if (pid == -1)
			ft_error("pid", command);
		if (pid == 0)
			child_process(tools, command, pipefd);
		last_exit = parent_process(pid, pipefd, command);
		tools->last_exit_code = last_exit;
		command += next_command_index(command);
		if (*command && (*command)[0] == '|')
			command++;
	}
	dup2(std_in_fd[0], STDIN_FILENO);
	dup2(std_in_fd[1], STDOUT_FILENO);
	return (last_exit);
}

/*
** @return index of next pipe, if not found returns end of command
*/
int	next_command_index(char **command)
{
	int	i;

	i = -1;
	while (command[++i])
		if (command[i][0] == '|')
			break ;
	return (i);
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
