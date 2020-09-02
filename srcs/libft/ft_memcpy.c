/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 15:15:02 by imicah            #+#    #+#             */
/*   Updated: 2020/05/01 18:53:53 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t byte_sizes)
{
	const char	*temp_src = (char*)src;
	char		*temp_dest;

	temp_dest = (char*)dest;
	if (temp_dest == temp_src || byte_sizes == 0)
		return (dest);
	while (byte_sizes--)
		*(temp_dest++) = *(temp_src++);
	return (dest);
}
