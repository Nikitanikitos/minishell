/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:23:21 by imicah            #+#    #+#             */
/*   Updated: 2020/05/03 01:55:06 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result_s;
	size_t	i;

	i = 0;
	if (ft_strlen(s) < start)
		len = 0;
	if (!(result_s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len && s[start])
		result_s[i++] = s[start++];
	result_s[i] = '\0';
	return (result_s);
}
