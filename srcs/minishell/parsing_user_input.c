/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_and_parameters.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:12:06 by imicah            #+#    #+#             */
/*   Updated: 2020/09/17 11:24:55 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*single_parse(char **argument, t_list *env_list)
{
	char	*temp;
	char	*result;
	int 	i;
	int 	index;

	index = 0;
	result = NULL;
	while (**argument && !ft_strchr(" <>|;\'\"", **argument))
	{
		temp = NULL;
		if (**argument == '\\')
			(*argument)++;
		else if (**argument == '$')
			temp = parse_with_envp(argument, env_list);
		i = (temp) ? ft_strlen(temp) : 1;
		result = ft_realloc(result, i);
		if (temp)
		{
			ft_strcpy(result + index, temp);
			free(temp);
			index += i;
		}
		else
			result[index++] = *(*argument)++;
	}
	if (result)
		result[index] = 0;
	return (result);
}

char	*parse_single_quote(char **argument)
{
	char		*result;
	char		*temp;
	int			index;

	index = 0;
	result = NULL;
	temp = ++(*argument);
	while (temp[index] && temp[index] != '\'')
		index++;
	if (index)
		result = ft_strndup(temp, (size_t)index);
	temp += index;
	if (*temp)
		temp++;
	*argument = temp;
	return (result);

}

char	*parse_double_quote(char **argument, t_list *env_list)
{
	char	*temp_argument;
	char	*temp;
	char	*result;
	int 	i;
	int 	index;

	index = 0;
	result = NULL;
	temp_argument = ++(*argument);
	while (*temp_argument && *temp_argument != '\"')
	{
		temp = NULL;
		if (*temp_argument == '\\' && ft_strchr("\\$\"", *(temp_argument + 1)))
			temp_argument++;
		else if (*temp_argument == '$')
			temp = parse_with_envp(&temp_argument, env_list);
		i = (temp) ? ft_strlen(temp) : 1;
		result = ft_realloc(result, i);
		if (temp)
		{
			ft_strcpy(result + index, temp);
			free(temp);
			index += i;
		}
		else
			result[index++] = *temp_argument++;
	}
	*argument = ++temp_argument;
	if (result)
		result[index] = 0;
	return (result);
}

char	*parse_argument(char **user_input, t_list *env_list)
{
	int		argument_length;
	int 	shift;
	char	*temp_user_input;
	char	*result;
	char	*temp;

	temp_user_input = *user_input;
	result = NULL;
	shift = 0;
	while (*temp_user_input)
	{
		if (ft_isspace(*temp_user_input))
			break ;
		if (*temp_user_input == '\'')
			temp = parse_single_quote(&temp_user_input);
		else if (*temp_user_input == '\"')
			temp = parse_double_quote(&temp_user_input, env_list);
		else
			temp = single_parse(&temp_user_input, env_list);
		if (temp)
		{
			argument_length = ft_strlen(temp);
			result = ft_realloc(result, argument_length);
			ft_strcpy(result + shift, temp);
			shift += argument_length;
			free(temp);
		}
	}
	if (result)
		result[shift] = 0;
	*user_input = temp_user_input;
	return (result);
}

char	**parse_user_input(char **user_input, t_list *env_list)
{
	int		i;
	char	*argument;
	char 	*temp_user_input;
	char	**arguments;

	i = 0;
	arguments = NULL;
	temp_user_input = *user_input;
	while (*temp_user_input)
	{
		while (ft_isspace(*temp_user_input))
			temp_user_input++;
		if (*temp_user_input == ';' || !*temp_user_input)
			break ;
		argument = parse_argument(&temp_user_input, env_list);
		if (argument)
		{
			arguments = ft_double_realloc(arguments, 1);
			arguments[i++] = argument;
		}
	}
	*user_input = temp_user_input;
	return (arguments);
}
