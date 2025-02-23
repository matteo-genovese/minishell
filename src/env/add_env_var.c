/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:53:04 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/23 19:22:16 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_var(char *key, char *value, char ***envp)
{
	char	*joined_string;

	joined_string = ft_strjoin(key, value);
	export_variable(joined_string, envp);
	free(joined_string);
}
