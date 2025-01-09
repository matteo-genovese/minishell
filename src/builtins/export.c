/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:00:02 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/09 23:16:57 by fde-sist         ###   ########.fr       */
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

void	export_variable(char *name, char *value, char ***envp)
{
	int		i;
	char	**new_envp;

	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp(name, (*envp)[i], ft_strchr(name, '=') - name + 1))
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
	*envp = new_envp;
}

/*input: length of commands (export included),
list of arguments (export name1=value1 ...), envp */
void	export(int argc, char **argv, char ***envp)
{
	char	*value;
	int		i;

	i = -1;
	if (argc < 2)
	{
		export_no_args(*envp);
		return ;
	}
	while (++i < argc)
	{
		if (ft_strchr(argv[i], '='))
			export_variable(argv[i], ft_strchr(argv[i], '=') + 1, envp);
	}
}
