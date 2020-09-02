/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 02:15:32 by imicah            #+#    #+#             */
/*   Updated: 2020/04/30 22:59:22 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *arr1, const char *arr2, size_t byte_sizes)
{
	if (!byte_sizes)
		return (0);
	byte_sizes--;
	while (byte_sizes-- && *arr1 && *arr2 && (*arr1 == *arr2))
	{
		arr1++;
		arr2++;
	}
	return ((unsigned char)*arr1 - (unsigned char)*arr2);
}
