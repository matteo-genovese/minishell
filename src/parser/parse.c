/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:31:42 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/16 20:07:13 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*takes string and substitutes every space-like char into space*/
void	cleanup(char *input)
{
	while (*input)
	{
		if (*input < 13 && *input > 9)
			*input = ' ';
		input++;
	}
}

/*takes a string as an input and returns the array of its words*/
char	**parse(char *input, t_tools *tools, int last_exit_code)
{
	char	**output;
	int		i;
	char	*aux;

	if (!*input)
		return (NULL);
	cleanup(input);
	output = ft_split(input, ' ');
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
