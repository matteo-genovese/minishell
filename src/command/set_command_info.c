/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:17:18 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/24 12:02:49 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (command[i][0] == '|'
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
** checks if the file descriptor is valid
** @return -42 if the file descriptor is invalid
** @return -2 if the file descriptor is valid and dup2 was successful
*/
int	fd_redirect(char *file, int fd)
{
	int	changed_index;
	int	saved_char;

	if (file[ft_strlen(file) - 2] == '>' || file[ft_strlen(file) - 2] == '<')
		changed_index = ft_strlen(file) - 2;
	else
		changed_index = ft_strlen(file) - 1;
	saved_char = file[changed_index];
	file[changed_index] = '\0';
	if (ft_atoi(file) > 1023)
	{
		put_error("Bad file descriptor", file);
		file[changed_index] = saved_char;
		return (-42);
	}
	else
		dup2(fd, ft_atoi(file));
	file[changed_index] = saved_char;
	return (-2);
}

void	file_error(int fd, char *file)
{
	if (fd == -1)
	{
		if (errno == EACCES)
			put_error("Permission denied", file);
		else
			put_error("No such file or directory", file);
	}
}

/*
** TODO farsi passare il file descriptor precedente, se questo è
** valido allora chiudrelo
** 
** @return -1 if an error occurred, fd of opened file otherwise
*/
int	set_fd(char **file, int open_flag, int i)
{
	int	fd;

	if (is_directory(file[i + 1])
		&& open_flag == (O_WRONLY | O_CREAT | O_TRUNC))
	{
		put_error(": Is a directory", file[i + 1]);
		return (-1);
	}
	if (is_directory(file[i + 1])
		&& open_flag == (O_CREAT | O_APPEND | O_WRONLY))
	{
		put_error(": Is a directory", file[i + 1]);
		return (-1);
	}
	fd = open(file[i + 1], open_flag, 00644);
	if (file[i][0] == '<' || file[i][0] == '>')
	{
		file_error(fd, file[i + 1]);
		return (fd);
	}
	else
		return (fd_redirect(file[i], fd));
}

/*
** sets every file_descriptor for command_info, 
** if any is set to -41, an opening error occoured
*/
void	set_redirection(char **command, t_command *command_info, t_parser_result *parsed_info)
{
	int	i;

	i = 0;
	while (command[i] && (command[i][0] != '|' || parsed_info->quotes[i]))
	{
		if (count_words(command[i], ' ') > 1)
		{
			++i;
			continue ;
		}
		if (ft_strlen(command[i]) > 1 && !ft_strncmp(command[i] + ft_strlen(command[i]) - 2, "<<", 2)
			&& command_info->in_fd != -1 && command_info->out_fd != -1)
			command_info->in_fd = heredoc(command[i + 1]);
		else if (command[i][0] && !ft_strncmp(command[i] + ft_strlen(command[i]) - 1, "<", 1)
			&& command_info->in_fd != -1 && command_info->out_fd != -1)
			command_info->in_fd = set_fd(command, O_RDONLY, i);
		if (ft_strlen(command[i]) > 1 && !ft_strncmp(command[i] + ft_strlen(command[i]) - 2, ">>", 2)
			&& command_info->out_fd != -1 && command_info->in_fd != -1)
			command_info->out_fd = set_fd(command,
					O_WRONLY | O_APPEND | O_CREAT, i);
		else if (command[i][0] && !ft_strncmp(command[i] + ft_strlen(command[i]) - 1, ">", 1)
			&& command_info->out_fd != -1 && command_info->in_fd != -1)
			command_info->out_fd = set_fd(command,
					O_WRONLY | O_CREAT | O_TRUNC, i);
		// va chiuso l'fd prcedente se mettiamo due redirect dello stesso tipo
		i++;
	}
	if (command[i] && !ft_strncmp(command[i], "|", 2)
		&& command_info->out_fd == 1)
		command_info->out_fd = -42;
}

/*
** @return the last char of a string
*/
char	get_last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i == 0)
		return (0);
	return (str[i - 1]);
}

/*
**	@returns the number of strings in strs that do not contain a redirection
*/
int	len_no_redirect(t_parser_result *strs)
{
	int	i;
	int	output;

	i = 0;
	output = 0;
	if (!strs)
		return (0);
	while (strs->command[i] && (strs->command[i][0] != '|' || strs->quotes[i]))
	{
		if (count_words(strs->command[i], ' ') > 1)
		{
			output++;
			i++;
			continue ;
		}
		if ((get_last_char(strs->command[i]) != '<' && get_last_char(strs->command[i]) != '>' ) || strs->quotes)
			output++;
		else
			i++;
		i++;
	}
	return (output);
}

/*
** @return a string array with all the commands that do not contain a redirection
*/
char **command_setup(t_parser_result *parsed_input)
{
	int		i;
	int		j;
	char	**output;

	i = 0;
	j = 0;
	if (!parsed_input->command)
		return (NULL);
	output = (char **) malloc(sizeof(char *) * (len_no_redirect(parsed_input) + 1));
	while (parsed_input->command[i] && (parsed_input->command[i][0] != '|' || parsed_input->quotes[i]))
	{
		if (parsed_input->quotes[i])
		{
			output[j++] = ft_strdup(parsed_input->command[i]);
			i++;
			continue ;
		}
		if ((get_last_char(parsed_input->command[i]) != '<'
			&& get_last_char(parsed_input->command[i]) != '>')
			|| parsed_input->quotes[i])
			output[j++] = ft_strdup(parsed_input->command[i]);
		else
			i++;
		i++;
	}
	output[j] = NULL;
	return (output);
}

/*
** @return t_command * to all the information needed
**  to execute execve with pipe and redirections
** 
** commnad->in_fd = -42 means you have to handle here doc
** 
** commnad->out_fd = -42 means you have to redirect with pipe
*/
t_command	*set_command_info(t_parser_result *parsed_input, char **envp)
{
	t_command	*output;
	char		**paths;

	output = (t_command *)ft_calloc(1, sizeof(t_command));
	output->out_fd = STDOUT_FILENO;
	paths = find_path(envp, 0);
	output->command_with_path = set_command(parsed_input->command, paths, envp);
	set_redirection(parsed_input->command, output, parsed_input);
	output->args = command_setup(parsed_input);
	free_string_array(paths);
	return (output);
}
