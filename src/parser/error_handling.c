/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: starry <starry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:35:56 by starry            #+#    #+#             */
/*   Updated: 2025/02/22 13:35:56 by starry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	double_char_handler(char *sub, char *to_free)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '",
		STDERR_FILENO);
	if (sub[1])
		ft_putchar_fd(sub[1], STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	free(to_free);
	return (false);
}

bool	exceeded_count_handler(char *sub, char last_char, char *to_free)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putchar_fd(last_char, STDERR_FILENO);
	if (sub[1] && sub[1] == last_char)
		ft_putchar_fd(last_char, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	free(to_free);
	return (false);
}

void	*init_error_handler(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (NULL);
}
