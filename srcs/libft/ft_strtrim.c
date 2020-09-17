/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:52:04 by imicah            #+#    #+#             */
/*   Updated: 2020/04/30 23:24:34 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *s2)
{
	char	*result;
	int		len;
	int		i;

	i = 0;
	while (ft_strchr(s2, *s1) && *s1)
		s1++;
	len = ft_strlen(s1);
	while (ft_strchr(s2, s1[len - 1]) && *s1)
		len--;
	if (!(result = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = 0;
	return (result);
}
