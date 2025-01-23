/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:48:54 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/23 15:24:53 by fde-sist         ###   ########.fr       */
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
int	invalid_command(char **command, char *command_with_path)
{
	int	output;

	output = 0;
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
int	execute_command(char **envp, char **command)
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
		{
			ft_putstr_fd("minishell: pipe error\n", 2);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("minishell: fork error\n", 2);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			exit (child_process(envp, command, pipefd));
		}
		last_exit = parent_process(pid, pipefd, command);
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


int	child_process(char **envp, char **command, int pipefd[2])
{
	t_command	*command_info;
	int			exit_value;

	command_info = set_command_info(command, envp);
	exit_value = invalid_command(command, command_info->command_with_path);
	if (exit_value)
	{
		free(command_info);
		close(pipefd[0]);
		close(pipefd[1]);
		return (exit_value);
	}
	if (command_info->in_fd == -1 || command_info->out_fd == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_string_array(command);
		free(command_info->command_with_path);
		free(command_info);
		return (EXIT_FAILURE);
	}
	if (command_info->in_fd != 0)
		dup2(command_info->in_fd, STDIN_FILENO);
	if (command_info->out_fd != -42)
		dup2(command_info->out_fd, STDOUT_FILENO);
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	signal(SIGQUIT, SIG_DFL);
	return (execve(command_info->command_with_path, command, envp));
}

/*Checks if child process exited and handles SIGINT*/
int	parent_process(int pid, int pipefd[2], char **command)
{
	int			status;
	static int	exit_code;

	signal(SIGINT, SIG_IGN);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	status = 0;
	if (*(command + next_command_index(command)) == NULL)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(2, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 20);
		}
		signal(SIGINT, signal_handler);
		if (WIFSIGNALED(status))
			return (WTERMSIG(status) + 128);
		return (WEXITSTATUS(status));
	}
	else
	{
		waitpid(pid, &status, WNOHANG);
		if (WIFSIGNALED(status))
			return (WTERMSIG(status) + 128);
		return (WEXITSTATUS(status));
	}
	signal(SIGINT, signal_handler);
	return (1);
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
