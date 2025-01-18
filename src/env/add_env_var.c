/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:53:04 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/17 18:44:24 by starry           ###   ########.fr       */
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
