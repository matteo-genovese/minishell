/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:52:47 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/13 17:11:42 by fde-sist         ###   ########.fr       */
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
	user = ft_strjoin(temp, ":");
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
	while (*str)
	{
		ft_putstr_fd("\"", 2);
		ft_putstr_fd(*str, 2);
		ft_putstr_fd("\" ", 2);
		str++;
	}
	ft_putstr_fd("\n", 2);
}


int	main(int argc, char **argv, char **enviroment)
{
	char	*input;
	char	**command;
	t_tools	*tool;
	int		last_exit_code;
	char	*mini;

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
		if (!command || !*command)
		{
			free(command);
			free(input);
			continue ;
		}
		if (ft_strncmp(command[0], "exit", 5) == 0)
			ft_exit(command, input, tool, last_exit_code);
		if (ft_strncmp(command[0], "env", 4) == 0 && !command[1])
			env(tool->envp);
		else if (ft_strncmp(command[0], "pwd", 4) == 0)
			pwd();
		else if (ft_strncmp(command[0], "cd", 3) == 0)
			cd(command, tool);
		else if (ft_strncmp(command[0], "echo", 5) == 0)
			echo(command);
		else if (ft_strncmp(command[0], "export", 7) == 0)
			export(command, &(tool->envp));
		else if (ft_strncmp(command[0], "unset", 6) == 0)
			unset(command, &(tool->envp));
		else
			last_exit_code = execute_command(tool->envp, command);
		free(input);
		free_string_array(command);
	}
	free(mini);
	return (0);
}
