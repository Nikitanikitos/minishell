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

	i = 0;
	if (!ft_strcmp(str, ">>"))
		i = 2;
	else if (ft_strchr("|><", str[i]))
		i = 1;
	else if (!ft_strchr("\'\";|><", str[i]))
		while (!ft_isspace(str[i]) && !ft_strchr(";|><\'\"\0", str[i]))
			i++;
	else if (str[i] == '\'')
		i = get_next_quote(str, '\'', i);
	else if (str[i] == '\"')
		i = get_next_quote(str, '\"', i);
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

t_list	*parse_user_input(char *user_input, int *length)
{
	int		i;
	char	*argument;
	t_list	*arguments_list;

	arguments_list = NULL;
	while (*user_input)
	{
		while (ft_isspace(*user_input))
		{
			(*length)++;
			user_input++;
		}
		if (*user_input == ';')
			return (arguments_list);
		i = get_length_argument(user_input);
		*length += i;
		argument = ft_strndup(user_input, (size_t)i);
		user_input += i;
		if (!ft_strcmp(argument, "\'\'") || !ft_strcmp(argument, "\"\""))
			free(argument);
		else if (arguments_list)
			ft_lstadd_back(&arguments_list, ft_lstnew(argument));
		else
			arguments_list = ft_lstnew(argument);
	}
	return (arguments_list);
}
