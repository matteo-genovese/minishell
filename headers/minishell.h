/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:50:38 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/11 10:56:59 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libs/libft/libft.h"

// STRUCTS
typedef struct s_tools
{
	char	**envp;
}	t_tools;

// ENV FNCS
void	copy_envp(t_tools *tools, char **envp);
void	add_env_var(char *key, char *value, char ***envp);

// BUILTINS
int		pwd(void);
int		cd(char *path);
int		env(char **envp);
int		echo(char *input);
void	unset_target(char *target, char ***envp);
void	unset(char **targets, char ***envp);
void	export(char **command, char ***envp);
void	export_variable(char *name, char ***envp);
void	export_no_args(char **envp);
char	**parse(char *input);
void	cleanup(char *input);
void	free_string_array(char **str);

#endif
