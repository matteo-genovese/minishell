/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:52:47 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/14 19:47:46 by fde-sist         ###   ########.fr       */
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

int	main(int argc, char **argv, char **enviroment)
{
	char	*input;
	char	**command;
	t_tools	*tool;
	int		last_exit_code;
	char	*mini;
	int 	tty_fd;

	last_exit_code = 0;
	if (argc != 1 && argv)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	tool = (t_tools *)malloc(sizeof(t_tools));
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
			ft_exit(NULL, input, tool, last_exit_code);
		if (*input)
			add_history(input);
		command = parse(input, tool, last_exit_code);
		print_string_array(command);
		tool->input = input;
		tool->command_start = command;
		tool->command_len = string_array_size(command);
		if (!command || !*command)
		{
			free(command);
			free(input);
			continue ;
		}
		if ((!command[3] || !command[2]) && strncmp(command[0], "exit", 5) == 0)
		{
			tty_fd = open("/dev/tty", O_WRONLY);
			if (tty_fd == -1)
				tty_fd = 2;
			ft_putstr_fd("exit\n", tty_fd);
			ft_exit(command, input, tool, last_exit_code);
		}
		last_exit_code = execute_command(tool, command);
		free(input);
		free_size_string_array(command, tool->command_len);
	}
	free(mini);
	return (0);
}
