/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 15:50:37 by imicah            #+#    #+#             */
/*   Updated: 2020/06/14 15:50:38 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(char *src, int size)
{
	char	*temp;

	temp = src;
	if (src != NULL)
	{
		size += ft_strlen(src);
		src = (char*)ft_calloc(1, (size_t)size);
		ft_strcpy(src, temp);
		free(temp);
	}
	else
		src = (char*)ft_calloc(1, (size_t)size);
	return (src);
}

char	**ft_double_realloc(char **src, int size)
{
	char	**temp;
	int		i;

	temp = src;
	i = 0;
	if (src)
	{
		size += ft_str_double_len(src);
		src = (char**)malloc(sizeof(char*) * (size + 1));
		while (i < size)
		{
			src[i] = temp[i];
			i++;
		}
		src[i] = NULL;
		free(temp);
	}
	else
	{
		src = (char**)malloc(sizeof(char*) * (size + 1));
		src[size] = NULL;
	}
	return (src);
}
