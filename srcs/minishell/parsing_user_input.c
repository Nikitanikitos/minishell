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

int		get_length_argument(char *str)
{
	int		i;
	int 	quote;

	i = 0;
	quote = 0;
	while (*str)
	{
		if (ft_strchr(" |><;", *str) && !quote)
			break;
		else if (ft_strchr("\"\'", *str) && !quote)
			quote = 1;
		else if (ft_strchr("\"\'", *str) && quote)
			quote = 0;
		str++;
		i++;
	}
	return (i);
}

void	parse_arguments_in_command(char **arguments, t_list *env_list)
{
	int 	i;

	i = 0;
	while (arguments[i])
	{
		if (arguments[i][0] == '\"')
			arguments[i] = parse_argument_with_double_quotes(arguments[i], env_list);
		else if (arguments[i][0] == '\'')
			arguments[i] = parse_argument_with_single_quotes(arguments[i]);
		else if (ft_strchr(arguments[i], '$'))
			arguments[i] = parse_with_envp(arguments[i], env_list);
		i++;
	}
}

char	**parse_user_input(char *user_input, int *length)
{
	int		i;
	int 	number_arguments;
	char	**arguments;

	number_arguments = 0;
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
		else if (!ft_strncmp(">>", user_input, 2))
			i = 2;
		else if (*user_input == '|' || *user_input == '>' || *user_input == '<')
			i = 1;
		else
			i = get_length_argument(user_input);
		if (i != 0)
		{
			arguments = ft_double_realloc(arguments, 1);
			arguments[number_arguments++] = ft_strndup(user_input, (size_t)i);
		}
		user_input += i;
		*length += i;
	}
	return (arguments);
}
