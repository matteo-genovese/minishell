/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:52:47 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/09 22:06:53 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;	

	if (argc != 1 && argv && envp)
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
		if (ft_strncmp(input, "env", 3) == 0)
			env(envp);
		else if (ft_strncmp(input, "pwd", 3) == 0)
			pwd();
		else if (ft_strncmp(input, "cd", 2) == 0)
			cd(input + 3);
		else if (ft_strncmp(input, "echo", 4) == 0)
			echo(input);
		// printf("Hai inserito: %s\n", input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
