/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 18:34:24 by imicah            #+#    #+#             */
/*   Updated: 2020/05/03 18:34:24 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_match(const char *big, const char *little, size_t len)
{
	while (len-- && *little)
	{
		if (*(big++) != *(little++))
			return (0);
	}
	if (*little)
		return (0);
	return (1);
}

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*result;

	if (little == big)
		return ((char*)big);
	else if (ft_strlen(little) > ft_strlen(big))
		return (NULL);
	while (*big && len)
	{
		if (*big == *little)
		{
			result = (char*)big;
			if (ft_match(big, little, len))
				return (result);
		}
		big++;
		len--;
	}
	return (NULL);
}
