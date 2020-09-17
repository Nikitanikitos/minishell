/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <froxanne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 19:28:16 by froxanne          #+#    #+#             */
/*   Updated: 2020/09/17 19:38:18 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_slash(char *str)
{
	int		i;
	int		size;
	char	*new;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\\')
			size++;
		i++;
	}
	if (!(new = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != '\\')
			new[size++] = str[i];
		i++;
	}
	new[size] = 0;
	free(str);
	return (new);
}
