/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:56:20 by imicah            #+#    #+#             */
/*   Updated: 2020/05/12 18:56:22 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(const char *string1, const char *string2)
{
	char					*result;
	unsigned int			i;
	unsigned int			len_new_string;

	i = 0;
	len_new_string = ft_strchr(string1, '\0') + ft_strchr(string2, '\0');
	if (!(result = (char*)malloc(sizeof(char) * (len_new_string + 1))))
		return (NULL);
	while (*string1)
		result[i++] = *(string1++);
	while (*string2)
		result[i++] = *(string2++);
	result[i] = 0;
	return (result);
}

char	*ft_strndup(const char *src, int len)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*src && len--)
		result[i++] = *(src++);
	result[i] = '\0';
	return (result);
}

t_list	*ft_lstnew(char *content)
{
	t_list	*element;

	if (!(element = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	element->content = content;
	element->next = NULL;
	return (element);
}

int		ft_strchr(const char *src, char c)
{
	const char *src_copy = src;

	while (*src_copy)
		if (*src_copy++ == c)
			return ((int)(src_copy - src));
	if (c == '\0')
		return ((int)(src_copy - src));
	return (0);
}

void	add_list(t_list **lst, char *content)
{
	t_list	*temp;
	char	*prev_content;

	if (*lst == NULL)
	{
		*lst = ft_lstnew(content);
		return ;
	}
	temp = (*lst);
	while ((*lst)->next)
		*lst = (*lst)->next;
	if (ft_strchr((*lst)->content, '\n'))
		(*lst)->next = ft_lstnew(content);
	else
	{
		prev_content = (*lst)->content;
		(*lst)->content = ft_strjoin(prev_content, content);
		free(content);
		free(prev_content);
	}
	*lst = temp;
}
