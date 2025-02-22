/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_result.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:35:50 by starry            #+#    #+#             */
/*   Updated: 2025/02/22 13:35:51 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_result	*parser_result_init(char **arr, bool *quotes)
{
	t_parser_result	*result;

	result = (t_parser_result *)malloc(sizeof(t_parser_result));
	if (!result)
		return (NULL);
	result->command = arr;
	result->quotes = quotes;
	return (result);
}

void	parser_result_free(t_parser_result *result)
{
	free(result->quotes);
	free(result);
}
