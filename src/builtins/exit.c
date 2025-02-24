/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:34:28 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/24 13:29:22 by fde-sist         ###   ########.fr       */
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
void	ft_exit(t_parser_result *parsed_input, char *input, t_tools *tool, int last_exit)
{
	int	exit_code;

	exit_code = 1;
	free(input);
	if (tool)
	{
		free_string_array(tool->envp);
		free(tool);
	}
	if (!parsed_input)
		exit(exit_code);
	if (parsed_input->command && (parsed_input->command[1] != NULL && parsed_input->command[2] != NULL))
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else if (parsed_input->command && parsed_input->command[1] == NULL)
		exit_code = last_exit;
	else if (parsed_input->command && are_all_digits(parsed_input->command))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(parsed_input->command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 2;
	}
	else if (parsed_input->command)
		exit_code = ft_atoi(parsed_input->command[1]);
	free_string_array(parsed_input->command);
	parser_result_free(parsed_input);
	exit (exit_code);
}
