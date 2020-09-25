/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 00:39:21 by imicah            #+#    #+#             */
/*   Updated: 2020/09/25 00:39:23 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_length_argument(char *user_input)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	if (!ft_strncmp(">>", user_input, 2))
		return (2);
	else if (*user_input == '|' || *user_input == '>' || *user_input == '<')
		return (1);
	while (*user_input)
	{
		if (ft_strchr(" |><;", *user_input) && !quote)
			break ;
		else if (ft_strchr("\"\'", *user_input) && !quote)
			quote = 1;
		else if (ft_strchr("\"\'", *user_input) && quote)
			quote = 0;
		user_input++;
		i++;
	}
	return (i);
}

int		is_double_quote(char *argument, int index, int quote)
{
	return (quote && ((argument[index] == '\''
			&& argument[index - 1] == '\'') || (argument[index] == '\"'
			&& argument[index - 1] == '\"')));
}
