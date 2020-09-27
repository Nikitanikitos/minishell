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
	int		i;
	int		index;

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
		result = ft_realloc(result, i + 1);
		if (temp)
			index += add_in_result(result, temp, i, index);
		else
			result[index++] = *(*argument)++;
	}
	(result) ? result[index] = 0 : 0;
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
	(*temp == '\'') ? temp++ : 0;
	*argument = temp;
	return (result);
}

char	*parse_double_quote(char **argument, t_list *env_list)
{
	char	*temp;
	char	*result;
	int		i;
	int		index;

	index = 0;
	result = NULL;
	(*argument)++;
	while (**argument && **argument != '\"')
	{
		temp = NULL;
		if (**argument == '\\' && ft_strchr("\\$\"", *(*argument + 1)))
			(*argument)++;
		else if (**argument == '$')
			temp = parse_with_envp(argument, env_list);
		i = (temp) ? ft_strlen(temp) : 1;
		result = ft_realloc(result, i + 1);
		if (temp)
			index += add_in_result(result, temp, i, index);
		else
			result[index++] = *(*argument)++;
	}
	(**argument == '\"') ? (*argument)++ : 0;
	(result) ? result[index] = 0 : 0;
	return (result);
}

char	*parse_argument(char **user_input, t_list *env_list)
{
	int		shift;
	char	*result;
	char	*temp;

	shift = 0;
	result = NULL;
	while (**user_input && !ft_strchr("|><;", **user_input))
	{
		if (ft_isspace(**user_input))
			break ;
		if (**user_input == '\'')
			temp = parse_single_quote(user_input);
		else if (**user_input == '\"')
			temp = parse_double_quote(user_input, env_list);
		else
			temp = single_parse(user_input, env_list);
		if (temp)
			shift += add_in_argument(&result, temp, shift);
	}
	if (result)
		result[shift] = 0;
	return (result);
}

char	**parse_user_input(char **usr_input, t_list *env_list, t_fds *fds)
{
	int			flag;
	int			i;
	char		*argument;
	char		**arguments;

	i = 0;
	flag = 0;
	arguments = NULL;
	while (**usr_input)
	{
		while (ft_isspace(**usr_input))
			(*usr_input)++;
		if (**usr_input == ';' || !**usr_input || (**usr_input == '|' && flag))
			break ;
		else if (**usr_input == '|' && !arguments)
			get_empty_pipe(usr_input, fds);
		else if (get_fd(usr_input, fds, env_list, &flag))
			break ;
		if ((argument = parse_argument(usr_input, env_list)))
		{
			arguments = ft_double_realloc(arguments, 1);
			arguments[i++] = argument;
		}
	}
	return (arguments);
}
