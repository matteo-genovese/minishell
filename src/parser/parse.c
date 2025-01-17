/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:31:42 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/17 11:42:29 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	reset_quote(int index, int *quote, int *flag_quote)
{
	*flag_quote = 1;
	quote[index] = !quote[index];
	if (quote[index] == 0)
		return (0);
	return (index + 1);
}

/*takes string and substitutes every space-like char into space*/
int	cleanup(char *input)
{
	int	quote[2];
	int	flag;
	int	flag_quote;

	quote[0] = 0;
	quote[1] = 0;
	flag = 0;
	flag_quote = 0;
	while (*input)
	{
		if (*input == '\'' && flag != 2)
			flag = reset_quote(0, quote, &flag_quote);
		if (*input == '\"' && flag != 1)
			flag = reset_quote(1, quote, &flag_quote);
		if (flag == 0)
		{
			if (*input < 13 && *input > 9)
				*input = ' ';
		}
		input++;
	}
	return (flag_quote);
}

/*takes a string as an input and returns the array of its words*/
char	**parse(char *input, t_tools *tools, int last_exit_code)
{
	char	**output;
	int		i;
	char	*aux;

	if (!*input)
		return (NULL);
	if (!cleanup(input))
		output = ft_split(input, ' ');
	else
		output = nuovo_split;		
	i = -1;
	while (output[++i])
	{
		if (output[i][0] == '$')
		{
			if (output[i][1] == '?')
				aux = ft_itoa(last_exit_code);
			else if (get_value_envp(output[i] + 1, tools->envp) == NULL)
				aux = ft_strdup("");
			else
				aux = ft_strdup(get_value_envp(output[i] + 1, tools->envp));
			free(output[i]);
			output[i] = ft_strdup(aux);
			free(aux);
		}
	}
	return (output);
}
