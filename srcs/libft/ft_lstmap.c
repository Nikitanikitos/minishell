/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:55:28 by imicah            #+#    #+#             */
/*   Updated: 2020/05/11 13:18:49 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*element;

	if (!(element = ft_lstnew(f(lst->content))))
	{
		ft_lstclear(&element, del);
		return (NULL);
	}
	lst = lst->next;
	result = element;
	while (lst)
	{
		if (!(element->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&result, del);
			break ;
		}
		element = element->next;
		lst = lst->next;
	}
	return (result);
}
