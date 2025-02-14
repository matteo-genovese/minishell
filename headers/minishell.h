/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:50:38 by fde-sist          #+#    #+#             */
/*   Updated: 2025/02/14 16:00:48 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libs/libft/libft.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>

/* STRUCTS */
typedef struct s_tools
{
	char						**envp;
	char						*input;
	char						**command_start;
	int							command_len;
	int							last_exit_code;
}								t_tools;

typedef struct s_command
{
	char						**args;
	char						*command_with_path;
	int							in_fd;
	int							out_fd;
}								t_command;

/* GLOBAL VAR */
extern volatile sig_atomic_t	g_signal;

/* SIGNAL HANDLING */
void							signal_handler(int sig);
void							sigchld_handler(int sig);

/* COMMAND EXEC*/
int								is_command(char *command, char **paths);
char							*set_command(char **command, char **paths,
									char **envp);
int								is_path(char *command);
char							*path_command(char **command, char **envp);
void							absolute_path_case(char **command,
									char **output);
int								execute_command(t_tools *tools, char **command);
int								is_special_command(char **command);
char							**find_path(char **envp, int index);
int								next_command_index(char **command);
void							child_process(t_tools *tools, char **command,
									int pipefd[2]);
int								parent_process(int pid, int pipefd[2],
									char **command);
int								invalid_command(char **command,
									char *command_with_path);
int								command_error_handler(t_command *command_info,
									int pipefd[2]);
t_command						*set_command_info(char **command, char **envp);

/* ENV FNCS*/
void							copy_envp(t_tools *tools, char **envp);
void							add_env_var(char *key, char *value,
									char ***envp);
char							*get_value_envp(char *name, char **envp);
void							set_shell_level(char ***envp);

/* BUILTINS */
int								pwd(void);
int								cd(char **command, t_tools *tools);
int								env(char **envp);
int								echo(char **command);
void							ft_exit(char **command, char *input,
									t_tools *tool, int last_exit);
void							unset_target(char *target, char ***envp);
void							unset(char **targets, char ***envp);
void							export(char **command, char ***envp);
void							export_variable(char *name, char ***envp);
void							export_no_args(char **envp);
char							**parse(char *input, t_tools *tools,
									int last_exit_code);

/* PARSER */
char							**parse(char *input, t_tools *tools,
									int last_exit_code);
char							*join_char(char *s, char c);
char							*joinfree(char *s, char *s2);
char							**stringarr_from_list(struct s_list *l);
char							*preprocessed(char *s, t_tools *tools,
									int last_exit_code);
bool							is_parser_separator(char c);
bool							is_exotic_char(char c);
size_t							handle_redirect(char *s, size_t j);

// UTILS
int								ft_n_args(char **command);
void							cleanup(char *input);
void							free_string_array(char **str);
void							ft_error(char *error_type, char **command);
int								is_directory(const char *path);
void							free_size_string_array(char **array, size_t size);
void							exit_clean_up(t_tools *tools, int exit_code);

#endif
