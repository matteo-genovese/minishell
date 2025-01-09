/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:25:54 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/19 22:40:46 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd_aux(long int n, int fd)
{
	char	aux;

	if (!n)
		return ;
	aux = '0' + (n % 10);
	ft_putnbr_fd_aux(n / 10, fd);
	write(fd, &aux, 1);
}

void	ft_putnbr_fd(int num, int fd)
{
	long int	n;

	n = (long int) num;
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (!n)
	{
		write(fd, "0", 1);
		return ;
	}
	ft_putnbr_fd_aux(n, fd);
}
