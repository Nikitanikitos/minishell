/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:41:20 by imicah            #+#    #+#             */
/*   Updated: 2020/09/02 15:41:22 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
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

void	parsing_user_input(char *user_input, char *command, char ***parameters)
{
	char	*temp_parsed_input;
	char	**parsed_input;

	parsed_input = ft_split(user_input, ' ');
	ft_strcpy(command, parsed_input[0]);
	while (*command)
	{
		if (*command == '\n' || *command == ' ')
			*command = 0;
		command++;
	}
	parsed_input++;
	*parameters = parsed_input;
	if (*parsed_input)
	{
		while (*(parsed_input + 1))
			parsed_input++;
		temp_parsed_input = *parsed_input;
		while (*temp_parsed_input)
		{
			if (*temp_parsed_input == '\n' || *temp_parsed_input == ' ')
				*temp_parsed_input = 0;
			temp_parsed_input++;
		}

	}
}

void	get_command_and_parameters(char *command, char ***parameters)
{
	char 	user_input[200] = "/bin/ls /";

	read_user_input(user_input);
	ft_bzero(command, 200);
	parsing_user_input(user_input, command, parameters);
}

int		main(int ac, char **av)
{
	char	command[100];
	char 	**parameters;
	char 	*parameterss[] = {"/", NULL};
	int 	status;

	while (TRUE)
	{
		type_prompt();
		get_command_and_parameters(command, &parameters);
		printf("command = %s$\n", command);
		while (*parameters != NULL)
			printf("parameter = %s$\n", *parameters++);
		if (fork())
			waitpid(-1, &status, 0);
		else
			execve(command, parameterss, 0);
		if (command[0] == 'q')
			break;
	}
	return 0;
}
