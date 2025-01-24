/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 23:12:35 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/23 23:25:37 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	child_process(char **envp, char **command, int pipefd[2])
{
	t_command	*command_info;
	int			error_exit;

	command_info = set_command_info(command, envp);
	error_exit = command_error_handler(command_info, pipefd);
	if (error_exit)
		return (error_exit);
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
		close(pipefd[0]);
		close(pipefd[1]);
		return (exit_value);
	}
	if (command_info->in_fd == -1 || command_info->out_fd == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_string_array(command_info->args);
		free(command_info->command_with_path);
		free(command_info);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
