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
		src = (char*)malloc(sizeof(char) * size);
		ft_strcpy(src, temp);
		free(temp);
	}
	else
		src = (char*)malloc(sizeof(char) * size);
	return (src);
}
