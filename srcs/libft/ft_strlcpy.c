/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:48:06 by imicah            #+#    #+#             */
/*   Updated: 2020/05/03 01:17:28 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t byte_sizes)
{
	const size_t	result = ft_strlen(src);
	const size_t	byte_sizes_copy = byte_sizes;

	if (byte_sizes > 0)
		byte_sizes = byte_sizes - 1;
	while (byte_sizes-- && *src)
		*(dst++) = *(src++);
	if (byte_sizes_copy)
		*dst = '\0';
	return (result);
}
