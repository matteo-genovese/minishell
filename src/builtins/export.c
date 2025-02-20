/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:00:02 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/20 22:20:11 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_no_args(char **envp)
{
	while (*envp)
	{
		printf("declare -x %s\n", *envp);
		envp++;
	}
}

int	check_if_already_set(char *name, char ***envp, int i)
{
	if (!ft_strncmp(name, (*envp)[i], ft_strchr(name, '=') - name)
		&& (ft_strchr(name, '=') - name)
		== ft_strchr((*envp)[i], '=') - (*envp)[i])
	{
		free((*envp)[i]);
		(*envp)[i] = ft_strdup(name);
		return (1);
	}
	return (0);
}

void	export_variable(char *name, char ***envp)
{
	int		i;
	char	**new_envp;

	i = -1;
	while ((*envp)[++i])
		if (check_if_already_set(name, envp, i))
			break ;
	if ((*envp)[i] != NULL)
		return ;
	new_envp = (char **)malloc((i + 2) * sizeof(char *));
	new_envp[i + 1] = NULL;
	i = -1;
	while ((*envp)[++i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		free((*envp)[i]);
	}
	new_envp[i] = ft_strdup(name);
	free(*envp);
	*envp = new_envp;
}

/*add a variable to our copy of envp*/
void	just_add(char *variable, char ***envp)
{
	int		i;
	char	**new_envp;

	i = -1;
	while ((*envp)[++i])
		if (!ft_strncmp(variable, (*envp)[i], ft_strlen(variable))
			&& (*envp)[i][ft_strlen(variable)] == '=')
			return ;
	new_envp = (char **)malloc((i + 2) * sizeof(char *));
	new_envp[i + 1] = NULL;
	i = -1;
	while ((*envp)[++i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		free((*envp)[i]);
	}
	new_envp[i] = ft_strdup(variable);
	free(*envp);
	*envp = new_envp;
}

/*
** checks if syntax of export is correct
** @returns 0 if correct, 1 if incorrect, 2 if correct with +
*/
int	export_check(char **command, char ***envp)
{
	int		i;
	char	**aux;
	char	*joined_sting;
	int		index;

	i = -1;
	if (command[1][0] == '=' || ft_isdigit(command[1][0]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(command[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (command[1][0] == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(command[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	while (command[1][++i] && command[1][i] != '=')
	{
		if (command[1][i] == '-')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(command[1], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		if (command[1][i] == '+' && command[1][i + 1] != '=')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(command[1], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		else if (command[1][i] == '+' && command[1][i + 1] == '=')
		{
			aux = ft_split(command[1], '=');
			index = ft_strlen(aux[0]) - 1;
			aux[0][index] = '\0';
			joined_sting = ft_strjoin(get_value_envp(aux[0], *envp), aux[1]);
			aux[0][index] = '=';
			if (joined_sting)
			{
				add_env_var(aux[0], joined_sting, envp);
				free(joined_sting);
			}
			else
				add_env_var(aux[0], aux[1], envp);
			free_string_array(aux);
			return (2);
		}
	}
	return (0);
}

/*
** takes as an input a command and enviroment variables,
** adds enviroment variable to the list 
*/
int	export(char **command, char ***envp)
{
	int		lenght;
	int		i;
	int		check_value;

	lenght = 0;
	while (command[lenght])
		lenght++;
	if (lenght < 2)
	{
		export_no_args(*envp);
		return (EXIT_SUCCESS);
	}
	check_value = export_check(command, envp);
	if (check_value == 1)
		return (EXIT_FAILURE);
	if (check_value == 2)
		return (EXIT_SUCCESS);
	i = 0;
	while (++i < lenght)
	{
		if (ft_strchr(command[i], '='))
			export_variable(command[i], envp);
		else
			just_add(command[i], envp);
	}
	return (EXIT_SUCCESS);
}
