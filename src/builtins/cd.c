/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:09:17 by mgenoves          #+#    #+#             */
/*   Updated: 2025/01/12 12:56:34 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	cd(char **command, t_tools *tools)
{
	int		i;
	char	*pwd;
	int		n_args;

	n_args = 0;
	while (command[n_args])
		n_args++;
	i = 0;
	while (command[1] && command[1][i] == ' ')
		i++;
	pwd = getcwd(NULL, 0);
	if (n_args == 1 || ft_strncmp(command[1] + i, "~", 2) == 0)
	{
		if (getvalue_global_variable("HOME", tools->envp) == NULL)
		{
			ft_putstr_fd("Error: HOME not set\n", 2);
			free(pwd);
			return (EXIT_FAILURE);
		}
		unset_target("OLDPWD", &tools->envp);
		add_env_var("OLDPWD=", getcwd(NULL, 0), &tools->envp);
		chdir(getvalue_global_variable("HOME", tools->envp));
		unset_target("PWD", &tools->envp);
		add_env_var("PWD=", getcwd(NULL, 0), &tools->envp);
		free(pwd);
		return (EXIT_SUCCESS);
	}
	else if (chdir(command[1] + i) == -1)
	{
		ft_putstr_fd("Error: no such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	else
	{
		unset_target("OLDPWD", &tools->envp);
		add_env_var("OLDPWD=", pwd, &tools->envp);
		pwd = getcwd(NULL, 0);
		unset_target("PWD", &tools->envp);
		add_env_var("PWD=", pwd, &tools->envp);
		free(pwd);
	}
	return (EXIT_SUCCESS);
}

