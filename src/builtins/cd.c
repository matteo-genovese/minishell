/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:09:17 by mgenoves          #+#    #+#             */
/*   Updated: 2025/01/12 14:43:56 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	cd_home(t_tools *tools)
{
	if (getvalue_global_variable("HOME", tools->envp) == NULL)
	{
		ft_putstr_fd("Error: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	unset_target("OLDPWD", &tools->envp);
	add_env_var("OLDPWD=", getcwd(NULL, 0), &tools->envp);
	chdir(getvalue_global_variable("HOME", tools->envp));
	unset_target("PWD", &tools->envp);
	add_env_var("PWD=", getcwd(NULL, 0), &tools->envp);
	return (EXIT_SUCCESS);
}

static int	set_pwd(t_tools *tools, char *pwd)
{
	unset_target("OLDPWD", &tools->envp);
	add_env_var("OLDPWD=", pwd, &tools->envp);
	pwd = getcwd(NULL, 0);
	unset_target("PWD", &tools->envp);
	add_env_var("PWD=", pwd, &tools->envp);
	return (EXIT_SUCCESS);
}

static int	ft_n_args(char **command)
{
	int	i;
	int	n_args;

	n_args = 0;
	while (command[n_args])
		n_args++;
	i = 0;
	while (command[1] && command[1][i] == ' ')
		i++;
	return (n_args);
}

int	cd(char **command, t_tools *tools)
{
	int		i;
	char	*pwd;

	i = 0;
	while (command[1] && command[1][i] == ' ')
		i++;
	pwd = getcwd(NULL, 0);
	if (ft_n_args(command) == 1 || ft_strncmp(command[1] + i, "~", 2) == 0)
	{
		free(pwd);
		if (cd_home(tools) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
	}
	else if (chdir(command[1] + i) == -1)
	{
		ft_putstr_fd("Error: no such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	else
		set_pwd(tools, pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
