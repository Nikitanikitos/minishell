/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:23:48 by imicah            #+#    #+#             */
/*   Updated: 2020/05/03 13:35:16 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	unsigned char		i;

	i = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	unsigned char		i;
	char				*result;
	char				pos_or_neg;

	i = ft_len(n);
	pos_or_neg = 1;
	if (!(result = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	result[i--] = '\0';
	if (n == 0)
		result[i--] = '0';
	else if (n < 0)
	{
		result[0] = '-';
		pos_or_neg = -1;
	}
	while (n)
	{
		result[i--] = ((n % 10) * pos_or_neg) + 48;
		n /= 10;
	}
	return (result);
}
