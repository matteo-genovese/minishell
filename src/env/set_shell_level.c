/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell_level.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:10 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/23 19:19:18 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shell_level(char ***envp)
{
	int		current_shlvl;
	char	*new_shell_lvl;

	current_shlvl = ft_atoi(get_value_envp("SHLVL", *envp));
	new_shell_lvl = ft_itoa(current_shlvl + 1);
	add_env_var("SHLVL=", new_shell_lvl, envp);
	free(new_shell_lvl);
}
