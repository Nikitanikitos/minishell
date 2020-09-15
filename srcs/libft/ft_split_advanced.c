/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_advanced.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:50:59 by imicah            #+#    #+#             */
/*   Updated: 2020/09/15 19:51:01 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_numbers_segment(char *str, char *separators)
{
	int8_t	flag;
	size_t	result;

	result = 0;
	flag = 1;
	while (*str)
	{
		if (!ft_strchr(separators, *str) && flag)
		{
			result++;
			flag = 0;
			while (!ft_strchr(separators, *str))
				str++;
		}
		else if (ft_strchr(separators, *str))
		{
			flag = 1;
			str++;
		}
	}
	return (result);
}

static size_t	get_segment_length(char *str, char *separators)
{
	size_t	result;

	result = 0;
	while (!ft_strchr(separators, *str++))
		result++;
	return (result);
}

char	**ft_split_advanced(char *str, char *separators)
{
	char	**result;
	size_t	numbers_segment;
	size_t	i;
	size_t	segment_length;

	i = 0;
	numbers_segment = get_numbers_segment(str, separators);
	if ((result = (char**)malloc(sizeof(char*) *
			(numbers_segment + 1))) == NULL)
		return (NULL);
	while (i < numbers_segment)
	{
		while (ft_strchr(separators, *str))
			str++;
		segment_length = get_segment_length(str, separators);
		if ((result[i] = ft_strndup(str, segment_length)) == NULL)
		{
			free_double_array(result);
			return (NULL);
		}
		str += segment_length;
		i++;
	}
	result[i] = NULL;
	return (result);
}
