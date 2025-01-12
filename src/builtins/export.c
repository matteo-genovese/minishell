/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:00:02 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/12 14:46:53 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	export_no_args(char **envp)
{
	while (*envp)
	{
		printf("declare -x %s\n", *envp);
		envp++;
	}
}

void	export_variable(char *name, char ***envp)
{
	int		i;
	char	**new_envp;

	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp(name, (*envp)[i], ft_strchr(name, '=') - name)
			&& (size_t)(ft_strchr(name, '=') - name) == ft_strlen((*envp)[i]))
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(name);
			break ;
		}
	}
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

/*takes as an input a command and enviroment variables,
adds enviroment variable to the list 
TODO non funzioan se ci sono più variabili ambientali con lo stesso nome*/
void	export(char **command, char ***envp)
{
	int		lenght;
	int		i;

	lenght = 0;
	while (command[lenght])
		lenght++;
	if (lenght < 2)
	{
		export_no_args(*envp);
		return ;
	}
	i = 0;
	while (++i < lenght)
	{
		if (ft_strchr(command[i], '='))
			export_variable(command[i], envp);
		else
			just_add(command[i], envp);
	}
}
