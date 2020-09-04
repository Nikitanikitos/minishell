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

void	print_command_and_parameters(t_command	*commands)
{
	char 	**params;

	params = commands->parameters;
	printf("command = %s$\n", commands->command);
	while (*params != NULL)
		printf("parameter = %s$\n", *(params)++);
}

int		main(void)
{
	int 		fd = open("test.txt", O_RDONLY);
	char		*user_input;
	t_command	*command;
	t_list		*commands_list;
	int			status;

	while (TRUE)
	{
		type_prompt();
		get_next_line(fd, &user_input);
		commands_list = get_commands_with_params_list(user_input);
//		free(user_input);
		command = (t_command*)commands_list->content;
		print_command_and_parameters(command);
		if (fork())
			waitpid(-1, &status, 0);
		else
			status = execve(command->command, command->parameters, 0);
		if (command->command[0] == 'q')
			break;
	}
	return 0;
}
