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

int 	get_next_quote(const char *str, char quote, int i)
{
	i++;
	while (str[i] != quote)
		i++;
	i++;
	return (i);
}

int		get_length_argument(char *str)
{
	int		i;

	i = 0;
	if (str[i] != '\'' && str[i] != '\"' && str[i] != ';')
		while (!ft_isspace(str[i]) && !ft_strchr(";\'\"\0", str[i]))
			i++;
	else if (str[i] == '\'')
		i = get_next_quote(str, '\'', i);
	else if (str[i] == '\"')
		i = get_next_quote(str, '\"', i);
	return (i);
}

t_list	*parse(char *str, int *length_sequence)
{
	int 	i;
	char	*argument;
	t_list	*arguments_list;

	arguments_list = NULL;
	while (*str)
	{
		while (ft_isspace(*str))
		{
			(*length_sequence)++;
			str++;
		}
		if (*str == ';')
			return (arguments_list);
		i = get_length_argument(str);
		*length_sequence += i;
		argument = ft_strndup(str, (size_t)i);
		str += i;
		if (!ft_strcmp(argument, "\'\'") || !ft_strcmp(argument, "\"\""))
			free(argument);
		else if (arguments_list)
			ft_lstadd_back(&arguments_list, ft_lstnew(argument));
		else
			arguments_list = ft_lstnew(argument);
	}
	return (arguments_list);
}

















