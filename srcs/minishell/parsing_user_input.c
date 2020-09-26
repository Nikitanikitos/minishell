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

int		add_in_result(char *result, char *temp, int i, int index)
{
	ft_strcpy(result + index, temp);
	free(temp);
	return (i);
}

char	*single_parse(char **argument, t_list *env_list)
{
	char	*temp;
	char	*result;
	int		i;
	int		index;

	index = 0;
	result = ft_realloc(NULL, 1);
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
			index += add_in_result(result, temp, i, index);
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
	char	*temp;
	char	*result;
	int		i;
	int		index;

	index = 0;
	result = ft_realloc(NULL, 1);
	(*argument)++;
	while (**argument && **argument != '\"')
	{
		temp = NULL;
		if (**argument == '\\' && ft_strchr("\\$\"", *(*argument + 1)))
			(*argument)++;
		else if (**argument == '$')
			temp = parse_with_envp(argument, env_list);
		i = (temp) ? ft_strlen(temp) : 1;
		result = ft_realloc(result, i);
		if (temp)
			index += add_in_result(result, temp, i, index);
		else
			result[index++] = *(*argument)++;
	}
	if (**argument == '\"')
		(*argument)++;
	if (result)
		result[index] = 0;
	return (result);
}

int		add_in_argument(char **result, char *temp, int shift)
{
	int		argument_length;

	argument_length = ft_strlen(temp);
	*result = ft_realloc(*result, argument_length);
	ft_strcpy(*result + shift, temp);
	free(temp);
	return (argument_length);
}

char	*parse_argument(char **user_input, t_list *env_list)
{
	int		shift;
	char	*result;
	char	*temp;

	result = ft_realloc(NULL, 1);
	shift = 0;
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
	if (result && !*result)
	{
		free(result);
		result = NULL;
	}
	else if (result)
		result[shift] = 0;
	return (result);
}

int		get_fd(char **temp_user_input, t_fds *fds, t_list *env_list, int *flag)
{
	if (**temp_user_input == '|')
	{
		fds->fork = 1;
		get_pipe_fd(temp_user_input, fds);
		return (1);
	}
	else if (**temp_user_input == '>')
	{
		fds->fork = 1;
		get_redirect_fd(temp_user_input, fds, env_list);
		*flag = 1;
	}
	else if (**temp_user_input == '<')
	{
		fds->back_redirect = 0;
		get_redirect_fd(temp_user_input, fds, env_list);
		dup2(fds->std_read, STDIN_FILENO);
	}
	return (0);
}

void	get_empty_pipe(char **temp_user_input, t_fds *fds)
{
	int		fd[2];

	(*temp_user_input)++;
	pipe(fd);
	close(fd[1]);
	fds->std_read = fd[0];
	dup2(fds->std_read, STDIN_FILENO);
	fds->fork = 0;
}

char	**parse_user_input(char **user_input, t_list *env_list, t_fds *fds)
{
	int			flag;
	int			i;
	char		*argument;
	char		**arguments;

	i = 0;
	flag = 0;
	arguments = NULL;
	while (**user_input)
	{
		while (ft_isspace(**user_input))
			(*user_input)++;
		if (**user_input == ';' || !**user_input ||
			(**user_input == '|' && flag))
			break ;
		else if (**user_input == '|' && !arguments)
			get_empty_pipe(user_input, fds);
		else if (get_fd(user_input, fds, env_list, &flag))
			break ;
		if ((argument = parse_argument(user_input, env_list)))
		{
			arguments = ft_double_realloc(arguments, 1);
			arguments[i++] = argument;
		}
	}
	return (arguments);
}
