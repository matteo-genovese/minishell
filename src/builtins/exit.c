/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:34:28 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/20 23:51:06 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if all the characters in the string are digits
*/
int	are_all_digits(char **command)
{
	int	i;
	int	j;

	i = 1;
	while (command[i])
	{
		j = 0;
		if (command[i][j] == '+' || command[i][j] == '-')
			j++;
		while (command[i][j])
		{
			if (!(command[i][j] >= '0' && command[i][j] <= '9'))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
** Exits the shell with aprpopriate exit_code
*/
void	ft_exit(char **command, char *input, t_tools *tool, int last_exit)
{
	int	exit_code;

	exit_code = 1;
	free(input);
	if (command && command[1] != NULL && command[2] != NULL)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else if (command && command[1] == NULL)
		exit_code = last_exit;
	else if (command && are_all_digits(command))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 2;
	}
	else if (command)
		exit_code = ft_atoi(command[1]);
	free_string_array(tool->envp);
	free(tool);
	rl_clear_history();
	if (command)
		free_string_array(command);
	exit (exit_code);
}
