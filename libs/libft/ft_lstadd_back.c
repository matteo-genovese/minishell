/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:07:55 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/20 18:05:39 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux_node;

	if (!lst || !new)
		return ;
	aux_node = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (aux_node->next)
		aux_node = aux_node->next;
	aux_node->next = new;
}
