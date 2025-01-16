/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:52:47 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/16 21:03:40 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

volatile sig_atomic_t	g_signal;

int	main(int argc, char **argv, char **enviroment)
{
	char				*input;
	char				**command;
	t_tools				*tool;
	int					last_exit_code;

	last_exit_code = 0;
	if (argc != 1 && argv)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	tool = (t_tools *)malloc(sizeof(t_tools));
	copy_envp(tool, enviroment);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	set_shell_level(&(tool->envp));
	while (1)
	{
		signal_handler(-42);
		input = readline("minishell> ");
		signal_handler(-41);
		g_signal = 0;
		if (!input)
		{
			printf("exit\n");
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		command = parse(input, tool, last_exit_code);
		if (!command)
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
	return (0);
}
