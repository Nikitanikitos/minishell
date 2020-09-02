/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 15:15:02 by imicah            #+#    #+#             */
/*   Updated: 2020/05/02 01:30:32 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t byte_sizes)
{
	const unsigned char	*temp_src = (unsigned char*)src;
	unsigned char		*temp_dest;

	temp_dest = (unsigned char*)dest;
	if (temp_src == temp_dest)
		return (dest);
	while (byte_sizes--)
	{
		if (*temp_src == c)
		{
			*(temp_dest++) = *temp_src;
			return (temp_dest);
		}
		*(temp_dest++) = *(temp_src++);
	}
	return (NULL);
}
