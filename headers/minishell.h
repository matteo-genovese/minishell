/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:50:38 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/16 21:04:00 by fde-sist         ###   ########.fr       */
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
# include <sys/stat.h>
# include "../libs/libft/libft.h"

/* STRUCTS */
typedef struct s_tools
{
	char	**envp;
}	t_tools;

/* GLOBAL VAR */
extern volatile sig_atomic_t	g_signal;

/* SIGNAL HANDLING */
void	signal_handler(int sig);

/* COMMAND EXEC*/
int		is_command(char *command, char **paths);
char	*set_command(char **command, char **paths, char **envp);
int		is_path(char *command);
char	*path_command(char **command, char **envp);
void	absolute_path_case(char **command, char **output);
int		execute_command(char **envp, char **command);
int		is_special_command(char **command);
char	**find_path(char **envp, int index);
int		father_process(int pid);

/* ENV FNCS*/
void	copy_envp(t_tools *tools, char **envp);
void	add_env_var(char *key, char *value, char ***envp);
char	*get_value_envp(char *name, char **envp);
void	set_shell_level(char ***envp);

/* BUILTINS */
int		pwd(void);
int		cd(char **command, t_tools *tools);
int		env(char **envp);
int		echo(char **command);
void	ft_exit(char **command, char *input, t_tools *tool, int last_exit);
void	unset_target(char *target, char ***envp);
void	unset(char **targets, char ***envp);
void	export(char **command, char ***envp);
void	export_variable(char *name, char ***envp);
void	export_no_args(char **envp);
char	**parse(char *input, t_tools *tools, int last_exit_code);

// UTILS
int		ft_n_args(char **command);
void	cleanup(char *input);
void	free_string_array(char **str);
int		is_directory(const char *path);

#endif
