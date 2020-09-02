/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:13:32 by imicah            #+#    #+#             */
/*   Updated: 2020/05/03 00:05:29 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *arr, int c, size_t byte_sizes)
{
	unsigned char	*temp_arr;

	temp_arr = (unsigned char*)arr;
	while (byte_sizes--)
	{
		if (c == *temp_arr)
			return (temp_arr);
		temp_arr++;
	}
	return (NULL);
}
