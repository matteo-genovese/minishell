/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:09:17 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/18 09:32:44 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(t_tools *tools)
{
	char	*pwd;

	if (get_value_envp("HOME", tools->envp) == NULL)
	{
		ft_putstr_fd("Error: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	add_env_var("OLDPWD=", pwd, &tools->envp);
	chdir(get_value_envp("HOME", tools->envp));
	free(pwd);
	pwd = getcwd(NULL, 0);
	add_env_var("PWD=", pwd, &tools->envp);
	free(pwd);
	return (EXIT_SUCCESS);
}

static int	set_pwd(t_tools *tools, char **pwd)
{
	add_env_var("OLDPWD=", *pwd, &tools->envp);
	free(*pwd);
	*pwd = getcwd(NULL, 0);
	add_env_var("PWD=", *pwd, &tools->envp);
	return (EXIT_SUCCESS);
}

int	cd(char **command, t_tools *tools)
{
	int		i;
	char	*pwd;

	i = 0;
	while (command[1] && command[1][i] == ' ')
		i++;
	if (ft_n_args(command) > 2)
	{
		ft_putstr_fd("Error: cd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
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
		free(pwd);
		return (EXIT_FAILURE);
	}
	else
		set_pwd(tools, &pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
