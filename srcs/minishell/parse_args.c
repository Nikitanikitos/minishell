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

char	*parse_with_envp(char *parameters, t_list *env_list)
{
	char	*result;
	char	*temp;
	int 	index;

	if (*parameters == '$')
	{
		result = ft_strdup(get_env_value(parameters, env_list));
		free(parameters);
	}
	else
	{
		index = str_get_index(parameters, '$');
		result = ft_strndup(parameters, (size_t)index);
		parameters += index;
		temp = result;
		result = ft_strjoin(result, get_env_value(parameters, env_list));
		free(temp);
	}
	return (result);
}

char	*parse_without_quotes(char *parameters, t_list *env_list)
{
	char	*result;
	char	*temp_result;
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
		temp_result = result;
		if (*parameters == '$')
			result = ft_strjoin(result, get_env_value(temp, env_list));
		else
			result = ft_strjoin(result, temp);
		if (*temp_result)
			free(temp_result);
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
	if (!*result)
		return (result);
	parameters = parse_without_quotes(result, env_list);
	free(result);
	return (parameters);
}
