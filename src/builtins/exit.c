/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:34:28 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/26 11:11:26 by starry           ###   ########.fr       */
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
		while (command[i][j] == '0' || (command[i][j] >= 9 && command[i][j] <= 13)
			|| command[i][j] == ' ')
			j++;
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

bool	modulo_str_greater(char *string, char *value)
{
	int		i;

	i = 0;
	while (string[i] == '0' || (string[i] >= 9 && string[i] <= 13)
		|| string[i] == ' ')
		i++;
	if (string[i] == '-')
	{
		i++;
		if (ft_isdigit(value[0]) || value[0] == '+')
			return (false);
		value++;
	}
	else if (value[0] == '-')
		return (false);
	if (string[i] == '+')
		i++;
	if (ft_strlen(string + i) > ft_strlen(value))
		return (true);
	if (ft_strlen(string + i) < ft_strlen(value))
		return (false);
	if (ft_strncmp(string + i, value, ft_strlen(value)) > 0)
		return (true);
	return (false);

}

/*
** Exits the shell with appropriate exit_code
*/
void	ft_exit(t_parser_result *parsed_input, char *input, t_tools *tool, int last_exit)
{
	long int	exit_code;

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
	else if ((parsed_input->command && are_all_digits(parsed_input->command))
		|| modulo_str_greater(parsed_input->command[1], "9223372036854775807")
		|| modulo_str_greater(parsed_input->command[1], "-9223372036854775808")
		|| !parsed_input->command[1][0])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(parsed_input->command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 2;
	}
	else if (parsed_input->command)
		exit_code = ft_long_atoi(parsed_input->command[1]);
	free_string_array(parsed_input->command);
	parser_result_free(parsed_input);
	exit (exit_code);
}
