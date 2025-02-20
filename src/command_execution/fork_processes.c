/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 23:12:35 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/20 22:31:07 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** @return if command is a builtin
*/
bool	is_builtin(char *command)
{
	if (ft_strncmp(command, "exit", 5) == 0)
		return (true);
	if (ft_strncmp(command, "env", 4) == 0)
		return (true);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(command, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(command, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(command, "export", 7) == 0)
		return (true);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

/*
** Executes the builtin command
*/
void	execute_builtin(char **command, t_tools *tool)
{
	int	exit_code;

	exit_code = -1;
	if (ft_strncmp(command[0], "exit", 5) == 0)
		ft_exit(command, tool->input, tool, tool->last_exit_code);
	else if (ft_strncmp(command[0], "env", 4) == 0 && !command[1])
		exit_code = env(tool->envp);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		exit_code = pwd();
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		exit_code = cd(command, tool);
	else if (ft_strncmp(command[0], "echo", 5) == 0)
		exit_code = echo(command);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		exit_code = export(command, &(tool->envp));
	else if (ft_strncmp(command[0], "unset", 6) == 0)
	{
		exit_code = 0;
		unset(command, &(tool->envp));
	}
	if (exit_code != -1)
		exit_clean_up(tool, exit_code);
}

/*
** Frees all malloced memory and exits with exit_code
*/
void	exit_clean_up(t_tools *tools, int exit_code)
{
	free(tools->input);
	free_size_string_array(tools->command_start, tools->command_len);
	free_string_array(tools->envp);
	exit(exit_code);
}

/*
** Executes the command and sets up the pipes
*/
void	child_process(t_tools *tools, char **command, int pipefd[2])
{
	t_command	*command_info;
	int			error_exit;

	error_exit = 0;
	command_info = set_command_info(&command, tools->envp);
	error_exit = command_error_handler(command_info, pipefd);
	if (error_exit)
		exit(error_exit);
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
	execute_builtin(command, tools);
	signal(SIGQUIT, SIG_DFL);
	execve(command_info->command_with_path, command, tools->envp);
	ft_putstr_fd("minishell: execve error\n", 2);
	free_string_array(command);
	exit_clean_up(tools, 127);
}

/*
** Checks if child process exited and handles SIGINT SIGQUIT
*/
int	parent_process(int pid, int pipefd[2], char **command)
{
	int			status;

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
		wait(NULL);
	}
	else
		waitpid(pid, &status, WNOHANG);
	signal(SIGINT, signal_handler);
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (WEXITSTATUS(status));
}

/*
** @return if command is not executed, returns bash error 
** code, otherwise returns 0
*/
int	command_error_handler(t_command *command_info, int pipefd[2])
{
	int	exit_value;

	exit_value = invalid_command(command_info->args,
			command_info->command_with_path);
	if (exit_value)
	{
		free(command_info);
		if (pipefd)
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
		return (exit_value);
	}
	if (command_info->in_fd == -1 || command_info->out_fd == -1)
	{
		if (pipefd)
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
		free_string_array(command_info->args);
		free(command_info->command_with_path);
		free(command_info);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
