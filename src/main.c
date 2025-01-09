/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:52:47 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/09 12:25:08 by fde-sist         ###   ########.fr       */
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
			break ;
		}
		if (*input)
			add_history(input);
		printf("Hai inserito: %s\n", input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
