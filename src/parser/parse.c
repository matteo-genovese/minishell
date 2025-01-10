/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:31:42 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/10 18:17:15 by fde-sist         ###   ########.fr       */
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
char	**parse(char *input)
{
	char	**output;

	if (!*input)
	return (NULL);
	cleanup(input);
	output = ft_split(input, ' ');
	return (output);
}

