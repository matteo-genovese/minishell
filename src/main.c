/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:52:47 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/22 10:40:31 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

char	*get_ministr(t_tools *tool)
{
	char	*pwd;
	char	*user;
	char	*temp;
	char	*cwd;

	if (get_value_envp("HOME", tool->envp) == NULL)
		return (NULL);
	temp = ft_strdup(get_value_envp("USER", tool->envp));
	user = ft_strjoin(temp, "@:");
	free(temp);
	cwd = getcwd(NULL, 0);
	if (ft_strncmp(cwd, get_value_envp("HOME", tool->envp),
			ft_strlen(cwd)) == 0
		&& (ft_strlen(cwd) == ft_strlen(get_value_envp("HOME", tool->envp))))
		temp = ft_strdup("~");
	else
		temp = ft_strdup(ft_strrchr(cwd, '/'));
	pwd = ft_strjoin(temp, "$ ");
	free(temp);
	temp = ft_strjoin(user, pwd);
	free(user);
	free(pwd);
	free(cwd);
	return (temp);
}

void	print_string_array(char **str)
{
	if (!str)
		return ;
	while (*str)
	{
		ft_putstr_fd("\"", 2);
		ft_putstr_fd(*str, 2);
		ft_putstr_fd("\" ", 2);
		str++;
	}
	ft_putstr_fd("\n", 2);
}

size_t	string_array_size(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	free_size_string_array(char **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

bool	is_all_same_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (false);
		i++;
	}
	return (true);
}

int	check_valid_command(char **command)
{
	int	i;

	i = -1;
	while (command && command[++i])
	{
		if (count_words(command[i], ' ') > 1)
			continue ;
		if (command[i + 1] == NULL && get_last_char(command[i]) == '|')
			return (2);
		if ((get_last_char(command[i]) == '<'
			|| get_last_char(command[i]) == '>'))
		{
			if (is_all_same_char(command[i], get_last_char(command[i])) && ft_strlen(command[i]) > 2)
			{
				ft_putstr_fd(
					"minishell: syntax error near unexpected token `", 2);
				ft_putchar_fd(get_last_char(command[i]), 2);
				ft_putchar_fd(get_last_char(command[i]), 2);
				ft_putstr_fd("'\n", 2);
				return (EXIT_FAILURE);
			}
			if (command[i + 1] == NULL)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
				return (EXIT_FAILURE);
			}
			else if (get_last_char(command[i + 1]) == '<'
				|| get_last_char(command[i + 1]) == '>'
				|| get_last_char(command[i + 1]) == '|')
			{
				ft_putstr_fd(
					"minishell: syntax error near unexpected token `", 2);
				ft_putchar_fd(command[i + 1][0], 2);
				ft_putstr_fd("'\n", 2);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

bool	are_pipes_in_command(char **command)
{
	int	i;

	i = -1;
	while (command && command[++i])
	{
		if (!strncmp(command[i], "|", 2))
			return (true);
	}
	return (false);
}

bool	special_command_check(char *command)
{
	if (ft_strncmp(command, "exit", 5) == 0)
		return (true);
	if (ft_strncmp(command, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(command, "export", 7) == 0)
		return (true);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

int	main(int argc, char **argv, char **enviroment)
{
	char			*input;
	t_parser_result	*parsed_input;
	t_tools			*tool;
	char			*mini;
	int				flag;

	if (argc != 1 && argv)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	tool = (t_tools *)malloc(sizeof(t_tools));
	parsed_input = NULL;
	copy_envp(tool, enviroment);
	signal(SIGCHLD, sigchld_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	set_shell_level(&(tool->envp));
	while (1)
	{
		signal_handler(-42);
		mini = get_ministr(tool);
		input = readline(mini);
		free(mini);
		signal_handler(-41);
		g_signal = 0;
		if (!input)
		{
			rl_clear_history();
			ft_putstr_fd("exit\n", 2);
			ft_exit(NULL, input, tool, tool->last_exit_code);
		}
		if (!*input)
		{
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);
		parsed_input = parse(input, tool, tool->last_exit_code);
		if (parsed_input == NULL)
		{
			tool->last_exit_code = 2;
			free(input);
			continue ;
		}
		tool->input = input;
		tool->command_start = parsed_input->command;
		tool->command_len = string_array_size(parsed_input->command);
		if (!parsed_input->command || !*(parsed_input->command))
		{
			parser_result_free(parsed_input);
			free(input);
			continue ;
		}
		if (check_valid_command(parsed_input->command) == EXIT_FAILURE)
		{
			tool->last_exit_code = 2;
			free(input);
			free_size_string_array(parsed_input->command, tool->command_len);
			continue ;
		}
		if (!are_pipes_in_command(parsed_input->command) && special_command_check(parsed_input->command[0]))
		{
			t_command *command_info = set_command_info(parsed_input, tool->envp);
			if (invalid_command(parsed_input->command, command_info->command_with_path))
			{
				free(input);
				free_size_string_array(parsed_input->command, tool->command_len);
				continue ;
			}
			if (command_info->in_fd != 0)
				dup2(command_info->in_fd, STDIN_FILENO);
			if (command_info->out_fd != -42)
				dup2(command_info->out_fd, STDOUT_FILENO);
			flag = 0;
			free(command_info->command_with_path);
			free_string_array(command_info->args);
			free(command_info);
			if (ft_strncmp(parsed_input->command[0], "exit", 5) == 0)
			{
				rl_clear_history();
				ft_putstr_fd("exit\n", 2);
				ft_exit(parsed_input, input, tool, tool->last_exit_code);
			}
			if (ft_strncmp(parsed_input->command[0], "cd", 3) == 0)
			{
				tool->last_exit_code = cd(parsed_input->command, tool);
				flag = 1;
			}
			if (ft_strncmp(parsed_input->command[0], "export", 7) == 0)
			{
				tool->last_exit_code = export(parsed_input->command, &(tool->envp));
				flag = 1;
			}
			if (ft_strncmp(parsed_input->command[0], "unset", 6) == 0)
			{
				tool->last_exit_code = unset(parsed_input->command, &(tool->envp));
				flag = 1;
			}
			if (flag)
			{
				free(input);
				parser_result_free(parsed_input);
				free_size_string_array(tool->command_start, tool->command_len);
				continue ;
			}
		}
		tool->last_exit_code = execute_command(tool, parsed_input);
		parser_result_free(parsed_input);
		free_size_string_array(tool->command_start, tool->command_len);
		free(input);
	}
	return (0);
}
