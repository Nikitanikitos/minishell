/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 15:15:02 by imicah            #+#    #+#             */
/*   Updated: 2020/05/01 23:31:08 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *dest, int symb, size_t byte_sizes)
{
	char	*temp_dest;

	temp_dest = (char*)dest;
	while (byte_sizes--)
		*(temp_dest++) = symb;
	return (dest);
}
