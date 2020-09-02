/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 15:15:02 by imicah            #+#    #+#             */
/*   Updated: 2020/04/30 23:06:34 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dest, size_t byte_sizes)
{
	char	*temp_dest;

	temp_dest = (char*)dest;
	while (byte_sizes--)
		*(temp_dest++) = 0;
}
