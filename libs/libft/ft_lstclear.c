/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:36:59 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/20 18:45:53 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux_node;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		aux_node = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(aux_node, del);
	}
	lst = NULL;
}
