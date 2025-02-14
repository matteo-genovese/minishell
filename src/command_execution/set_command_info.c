/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:17:18 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/14 19:13:47 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** @return first occurance of '>', '<', or '|'
** if its not found returns last index of command
*/
int	special_char_index(char **command)
{
	int	i;

	i = -1;
	while (command[++i])
	{
		if (command[i][0] == 0 || command[i][0] == '|'
			|| command[i][0] == '>' || command[i][0] == '<')
			return (i);
	}
	return (i);
}

/*
** outputs to standard error "minishell: {error}: {str}\n"
*/
void	put_error(char *str, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

/*
** @return -1 if an error occurred, fd of opened file otherwise
*/
int	set_fd(char *file, int open_flag)
{
	int	fd;

	if (is_directory(file) && open_flag == (O_WRONLY | O_CREAT | O_TRUNC))
	{
		put_error(": Is a directory", file);
		return (-1);
	}
	if (is_directory(file) && open_flag == (O_CREAT | O_APPEND | O_WRONLY))
	{
		put_error(": Is a directory", file);
		return (-1);
	}
	fd = open(file, open_flag, 00644);
	if (fd == -1)
	{
		if (errno == EACCES)
			put_error("Permission denied", file);
		else
			put_error("No such file or directory", file);
	}
	return (fd);
}

/*
** sets every file_descriptor for command_info, 
** if any is set to -41, an opening error occoured
*/
void	set_redirection(char **command, t_command *command_info)
{
	int	i;

	i = 0;
	while (command[i] && command[i][0] != '|')
	{
		if (!strncmp(command[i], "<<", 2) && command_info->in_fd != -1)
			command_info->in_fd = heredoc(command[i + 1]);
		else if (!strncmp(command[i], "<", 1) && command_info->in_fd != -1)
			command_info->in_fd = set_fd(command[i + 1], O_RDONLY);
		if (!strncmp(command[i], ">>", 2) && command_info->out_fd != -1)
			command_info->out_fd = set_fd(command[i + 1],
					O_WRONLY | O_APPEND | O_CREAT);
		else if (!strncmp(command[i], ">", 1) && command_info->out_fd != -1)
			command_info->out_fd = set_fd(command[i + 1],
					O_WRONLY | O_CREAT | O_TRUNC);
		i++;
	}
	if (command[i] && !strncmp(command[i], "|", 1) && command_info->out_fd == 1)
		command_info->out_fd = -42;
}

/*
** @return t_command * to all the information needed
**  to execute execve with pipe and redirections
** 
** commnad->in_fd = -42 means you have to handle here doc
** 
** commnad->out_fd = -42 means you have to redirect with pipe
*/
t_command	*set_command_info(char **command, char **envp)
{
	t_command	*output;
	char		**paths;
	int			index;

	output = (t_command *)ft_calloc(1, sizeof(t_command));
	output->out_fd = STDOUT_FILENO;
	output->args = command;
	paths = find_path(envp, 0);
	output->command_with_path = set_command(command, paths, envp);
	set_redirection(command, output);
	index = special_char_index(command);
	free(output->args[index]);
	output->args[index] = NULL;
	free_string_array(paths);
	return (output);
}
