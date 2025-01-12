/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:03:43 by mgenoves          #+#    #+#             */
/*   Updated: 2025/01/12 22:31:28 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_quotes(char **str)
{
	int	i;
	int	j;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'' && !double_quote)
				single_quote = !single_quote;
			else if (str[i][j] == '\"' && !single_quote)
				double_quote = !double_quote;
			j++;
		}
		i++;
	}
	return (single_quote || double_quote);
}

static void	print_echo(int i, char **command, int *quote)
{
	int	j;	

	j = -1;
	while (command[i][++j])
	{
		if (command[i][j] == '\'' && !quote[1])
			quote[0] = !quote[0];
		else if (command[i][j] == '\"' && !quote[0])
			quote[1] = !quote[1];
		if ((command[i][j] != '\'' || quote[1]) &&
			(command[i][j] != '\"' || quote[0]))
			ft_putchar_fd(command[i][j], 1);
	}
	if (command[i + 1])
		ft_putchar_fd(' ', 1);
}

int	echo(char **command)
{
	int	i;
	int	n_flag;
	int	quote[2];

	n_flag = (command[1] && !ft_strncmp(command[1], "-n", 2));
	i = n_flag;
	if (check_quotes(command + i + 1))
	{
		ft_putstr_fd("Error: unmatched quote\n", 2);
		return (EXIT_FAILURE);
	}
	quote[0] = 0;
	quote[1] = 0;
	while (command[++i])
		print_echo(i, command, quote);
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
