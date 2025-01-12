/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:53:04 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/12 12:34:31 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_env_var(char *key, char *value, char ***envp)
{
	char	*joined_string;

	joined_string = ft_strjoin(key, value);
	export_variable(joined_string, envp);
	free(joined_string);
}
