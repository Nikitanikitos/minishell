/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_double_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:17:19 by imicah            #+#    #+#             */
/*   Updated: 2020/09/15 17:17:21 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_double_len(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int		is_correct_number(char *argument)
{
	if (*argument == '-' || *argument == '+')
		argument++;
	if (*argument == '\0')
		return (0);
	while (*argument)
		if (!ft_digit(*argument++))
			return (0);
	return (1);
}
