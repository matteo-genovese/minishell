/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:55:14 by fde-sist          #+#    #+#             */
/*   Updated: 2024/02/20 11:30:02 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*start;

	if (!lst)
		return (NULL);
	new_list = ft_lstnew((*f)(lst->content));
	if (!new_list)
	{
		ft_lstclear(&new_list, del);
		return (NULL);
	}
	start = new_list;
	lst = lst->next;
	while (lst)
	{
		new_list->next = ft_lstnew((*f)(lst->content));
		if (!new_list)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	return (start);
}
