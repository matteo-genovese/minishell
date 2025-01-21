/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:46:25 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/18 16:44:47 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_command_options	*redirect_handler(char **command)
{
	t_command_options	*output;
	int					i;

	output = (t_command_options *)malloc(sizeof(t_command_options));
	output->in_fd = STDIN_FILENO;
	output->out_fd = STDOUT_FILENO;
	output->is_append = 0;
	i = 0;
	while (command[i])
	{
		if (strncmp(command[i], ">", 2))
			//check se il successivo è un file con i permessi
			//setto il file descriptor, se già ne ho uno, chiudo il precedente

		if (strncmp(command[i], ">>", 3))

		if (strncmp(command[i], "<", 2))

		if (strncmp(command[i], "<<", 3))
		
		i++;
	}
}
