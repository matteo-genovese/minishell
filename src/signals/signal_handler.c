/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:04:24 by fde-sist          #+#    #+#             */
/*   Updated: 2025/01/15 17:12:51 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	signal_handler(int sig)
{
	static int	flag;

	g_signal = sig;
	if (sig == -42)
		flag = -1;
	if (sig == -41)
		flag = -2;
	if (sig < -40)
		return ;
	if (flag == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
