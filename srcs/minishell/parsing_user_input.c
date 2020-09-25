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

void	parse_arguments_in_command(char **arguments, t_list *env_list)
{
	int		i;

	i = 0;
	while (arguments[i])
	{
		if (arguments[i][0] == '\"')
			arguments[i] = parse_argument_with_double_quotes(arguments[i],
																	env_list);
		else if (arguments[i][0] == '\'')
			arguments[i] = parse_argument_with_single_quotes(arguments[i]);
		else if (ft_strchr(arguments[i], '$'))
			arguments[i] = parse_with_envp(arguments[i], env_list);
		i++;
	}
}

char	*copy_without_unused_quotes(int lenght, char *argument)
{
	char	*result;
	int		i;

	i = 0;
	result = (char*)malloc(sizeof(char) * (lenght + 1));
	while (*argument)
	{
		if (*argument != 1)
			result[i++] = *argument;
		argument++;
	}
	result[i] = 0;
	return (result);
}

int		handler_unused_quotes(char *argument, int index, int *quote)
{
	int		result;

	result = 0;
	if ((argument[index] == '\'' || argument[index] == '\"') && !*quote)
		*quote = 1;
	else if (is_double_quote(argument, index, *quote))
	{
		argument[index - 1] = 1;
		argument[index] = 1;
		result = 2;
		*quote = 0;
	}
	else if ((argument[index] == '\'' || argument[index] == '\"') && *quote)
		*quote = 0;
	else if (argument[index] == '\\' && !*quote)
	{
		argument[index] = 1;
		result = 1;
	}
	return (result);
}

char	*delete_unused_quotes(char *argument)
{
	char	*result;
	int		length;
	int		quote;
	int		index;

	length = ft_strlen(argument);
	quote = 0;
	index = 0;
	while (argument[index])
	{
		length -= handler_unused_quotes(argument, index, &quote);
		index++;
	}
	result = copy_without_unused_quotes(length, argument);
	free(argument);
	return (result);
}

char	**parse_user_input(char *user_input, int *length)
{
	int		length_argument;
	int		i;
	char	**arguments;

	i = 0;
	arguments = NULL;
	while (*user_input)
	{
		while (ft_isspace(*user_input))
		{
			(*length)++;
			user_input++;
		}
		if (*user_input == ';')
			return (arguments);
		if ((length_argument = get_length_argument(user_input)) != 0)
		{
			arguments = ft_double_realloc(arguments, 1);
			arguments[i++] = delete_unused_quotes(ft_strndup(user_input,
												(size_t)length_argument));
		}
		user_input += length_argument;
		*length += length_argument;
	}
	return (arguments);
}
