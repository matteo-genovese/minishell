/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:52:47 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/10 19:40:29 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char **argv, char **enviroment)
{
	char	*input;
	char	**command;
	t_tools	*tool;

	tool = (t_tools *)malloc(sizeof(t_tools));
	copy_envp(tool, enviroment);
	if (argc != 1 && argv)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		input = readline("minishell> ");
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
		if (ft_strncmp(command[0], "exit", 5)== 0)
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
			cd(input + 3);
		else if (ft_strncmp(command[0], "echo", 5) == 0)
			echo(input);
		else if (ft_strncmp(command[0], "export", 7) == 0)
			export(command, &(tool->envp));
		else if (ft_strncmp(command[0], "unset", 6) == 0)
			unset(command, &(tool->envp));
		free(input);
		free_string_array(command);
	}
	free_string_array(tool->envp);
	free(tool);
	rl_clear_history();
	printf("pisello");
	return (0);
}
