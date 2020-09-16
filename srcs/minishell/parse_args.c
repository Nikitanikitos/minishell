/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 21:22:29 by imicah            #+#    #+#             */
/*   Updated: 2020/09/16 21:22:31 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		str_get_index(const char *str, char element)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == element)
			return (i);
		i++;
	}
	return (-1);
}


char	*parse_without_quotes(char *parameters, t_list *env_list)
{
	char	*result;
	char	*temp;
	int 	index;

	result = "";
	while (*parameters)
	{
		if (*parameters == '$')
			index = str_get_index(parameters, ' ');
		else
			index = str_get_index(parameters, '$');
		if (index == -1)
			index = ft_strlen(parameters);
		temp = ft_strndup(parameters, (size_t)index);
		if (*parameters == '$')
			result = ft_strjoin(result, get_env_value(temp, env_list));
		else
			result = ft_strjoin(result, temp);
		free(temp);
		parameters += index;
	}
	return (result);
}

char	*parse_argument_with_single_quotes(char *parameters)
{
	char	*result;

	result = ft_strtrim(parameters, "\'");
	free(parameters);
	return (result);
}

char	*parse_argument_with_double_quotes(char *parameters, t_list *env_list)
{
	char	*result;

	result = ft_strtrim(parameters, "\"");
	free(parameters);
	parameters = result;
	result = parse_without_quotes(parameters, env_list);
	return (result);
}
