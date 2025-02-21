/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:41:51 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/21 10:21:27 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*frees a string pointer*/
void	free_string_array(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
