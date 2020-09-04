/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_and_parameters.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:12:06 by imicah            #+#    #+#             */
/*   Updated: 2020/09/02 20:12:07 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <printf.h>
#include "minishell.h"

void	type_prompt()
{
	static int	first_time = 1;

	if (first_time)
		write(1, " \e[1:1H\e[2J", 12);
	first_time = 0;
	write(1, "$", 1);
}

void	read_user_input(char *user_input)
{
	read(1, user_input, 200);
}

void	nullify_the_last_argument(char **parsed_parameters)
{
	char	*last_parameter;

	if (*parsed_parameters)
	{
		while (*(parsed_parameters + 1))
			parsed_parameters++;
		last_parameter = *parsed_parameters;
		while (*last_parameter)
		{
			if (*last_parameter == '\n' || *last_parameter == ' ')
			{
				*last_parameter = 0;
				break;
			}
			last_parameter++;
		}
	}
}

void	parsing_user_input(char *user_input, char *command, char ***parameters)
{
	char	**parsed_parameters;

	parsed_parameters = ft_split(user_input, ' ');
	ft_strcpy(command, parsed_parameters[0]);
	*parameters = parsed_parameters;
	nullify_the_last_argument(parsed_parameters);
}

void	get_command_and_parameters(char *command, char ***parameters)
{
	int 	fd = open("command.txt", O_RDONLY);
	char 	*user_input;

//	read_user_input(user_input);
	get_next_line(1, &user_input);
	ft_bzero(command, 200);
	parsing_user_input(user_input, command, parameters);
}