/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:26:14 by imicah            #+#    #+#             */
/*   Updated: 2020/05/03 15:43:24 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		ft_memcmp(const void *arr1, const void *arr2, size_t byte_sizes)
{
	const unsigned char	*temp_arr1 = (unsigned char*)arr1;
	const unsigned char	*temp_arr2 = (unsigned char*)arr2;

	if (temp_arr1 == temp_arr2 || !byte_sizes)
		return (0);
	byte_sizes--;
	while (byte_sizes-- && (*temp_arr1 == *temp_arr2))
	{
		temp_arr1++;
		temp_arr2++;
	}
	return (*temp_arr1 - *temp_arr2);
}
