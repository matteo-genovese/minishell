/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:50:38 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/12 21:00:52 by mgenoves         ###   ########.fr       */
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
# include <sys/wait.h>
# include "../libs/libft/libft.h"

// STRUCTS
typedef struct s_tools
{
	char	**envp;
}	t_tools;

// COMMAND EXEC
int		is_command(char *command, char **paths);
char	*set_command(char *command, char **paths, char **envp);
int		is_non_path(char *command);
char	*non_path_command(char *command, char **envp);
int		execute_command(char **envp, char **command);
int		is_special_command(char **command);
char	**find_path(char **envp, int index);

// ENV FNCS
void	copy_envp(t_tools *tools, char **envp);
void	add_env_var(char *key, char *value, char ***envp);
char	*getvalue_global_variable(char *name, char **envp);

// BUILTINS
int		pwd(void);
int		cd(char **command, t_tools *tools);
int		env(char **envp);
int		echo(char **command);
void	unset_target(char *target, char ***envp);
void	unset(char **targets, char ***envp);
void	export(char **command, char ***envp);
void	export_variable(char *name, char ***envp);
void	export_no_args(char **envp);
char	**parse(char *input);


// UTILS
int		ft_n_args(char **command);
void	cleanup(char *input);
void	free_string_array(char **str);

#endif
