/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:52:47 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/12 23:17:59y fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

volatile sig_atomic_t	g_signal;

void signal_handler(int sig) {
    g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **enviroment)
{
	char				*input;
	char				**command;
	t_tools				*tool;
	int					flag;
	struct sigaction	sa;

	tool = (t_tools *)malloc(sizeof(t_tools));
	copy_envp(tool, enviroment);
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	flag = 1;
	if (argc != 1 && argv)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		if (flag)
		input = readline("minishell> ");
		// ft_putnbr_fd(g_signal	, 1);
		// ft_putstr_fd(input, 1);
		if (g_signal == SIGINT)
			g_signal = 0;
		if (!input)
		{
			printf("exit\n");
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		command = parse(input);
		if (!command)
		{
			free(command);
			free(input);
			continue ;
		}
		if (ft_strncmp(command[0], "exit", 5) == 0)
		{
			free(input);
			free_string_array(command);
			break ;
		}
		if (ft_strncmp(command[0], "env", 4) == 0 && !command[1])
			env(tool->envp);
		else if (ft_strncmp(command[0], "pwd", 4) == 0)
			pwd();
		else if (ft_strncmp(command[0], "cd", 3) == 0)
			cd(command, tool);
		else if (ft_strncmp(command[0], "echo", 5) == 0)
			echo(input);
		else if (ft_strncmp(command[0], "export", 7) == 0)
			export(command, &(tool->envp));
		else if (ft_strncmp(command[0], "unset", 6) == 0)
			unset(command, &(tool->envp));
		else
			execute_command(tool->envp, command);
		free(input);
		free_string_array(command);
	}
	free_string_array(tool->envp);
	free(tool);
	rl_clear_history();
	printf("pisello");
	return (0);
}
