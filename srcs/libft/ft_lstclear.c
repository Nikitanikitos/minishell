/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:42:45 by imicah            #+#    #+#             */
/*   Updated: 2020/05/05 01:11:49 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_element;

	while (*lst)
	{
		next_element = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next_element;
	}
	*lst = NULL;
}
