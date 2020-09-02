/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 18:23:55 by imicah            #+#    #+#             */
/*   Updated: 2020/05/05 01:08:59 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t byte_sizes)
{
	void	*result;

	if (!(result = malloc(num * byte_sizes)))
		return (NULL);
	ft_bzero(result, num * byte_sizes);
	return (result);
}
