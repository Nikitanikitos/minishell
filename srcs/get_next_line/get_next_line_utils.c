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
	len_new_string = ft_strlen(string1) + ft_strlen(string2);
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
