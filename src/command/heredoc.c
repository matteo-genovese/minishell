/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:41:37 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/25 17:18:47 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** @return a string with the name of the file, it makss sure its unique
*/
char	*name_gen(void)
{
	char	*output;
	int		fd;
	char	*temp;
	char	*str;

	str = ft_itoa(getpid());
	output = ft_strjoin("/tmp/", str);
	free(str);
	while (1)
	{
		fd = open(output, O_RDWR | O_CREAT | O_EXCL, 00644);
		if (fd != -1)
			break ;
		else if (fd == -1 && errno != EEXIST)
		{
			ft_error("open here_doc", NULL);
			return (NULL);
		}
		else if (fd == -1 && errno == EEXIST)
		{
			temp = ft_strdup(output);
			free(output);
			output = ft_strjoin(temp, ft_itoa(getpid()));
			free(temp);
		}
		close(fd);
	}
	close(fd);
	return (output);
}

/*
** @return the file descriptor of the file created
** with the content of the heredoc
*/
int	heredoc(char *del)
{
	int		fd;
	char	*line;
	char	*filename;

	if (!del)
		ft_error("syntax error near unexpected token `newline'", NULL);
	filename = name_gen();
	fd = open(filename, O_WRONLY);
	if (fd == -1)
		ft_error("open here_doc", NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, del, ft_strlen(del) + 1))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	return (fd);
}
