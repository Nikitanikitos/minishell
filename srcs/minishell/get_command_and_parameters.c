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

#include "minishell.h"

void	type_prompt()
{
	static int	first_time = 1;

	if (first_time)
		write(1, " \e[1:1H\e[2J", 12);
	first_time = 0;
	write(1, "$", 1);
}

void	parsing_user_input(char *user_input, char *command, char ***parameters)
{
	int		len;
	char	**parsed_parameters;


//	parsed_parameters = ft_split(user_input, ' ');
//	while (*parsed_parameters)
//	{
//		if (ft_strchr(*parsed_parameters, ';'))
//			continue;
	}
//	ft_strcpy(command, parsed_parameters[0]);
//	*parameters = parsed_parameters;
}

void	get_command_and_parameters(t_list *commands_list)
{
	t_command	command;
	char	*parameters;
	int 	index;
	char 	*user_input;

	get_next_line(1, &user_input);
	
	while (user_input[index])
	{
		if (user_input[index] == ' ')
		{
			command.command = ft_strndup(user_input, index - 1);
			user_input += index + 1;
			index = 0;
			while (user_input[index] == ' ')
				index++;
		}
		else if (user_input[index] == ';')
		{
			parameters = ft_strndup(user_input, index - 1);
			command.parameters = ft_split(parameters, ' ');
			commands_list = ft_lstnew(&command);
		}
		index++;
	}
}
