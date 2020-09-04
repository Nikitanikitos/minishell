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

void	print_command_and_parameters(t_list	*commands_list)
{
	t_command	*command;

	while (commands_list)
	{
		printf("\n");
		command = (t_command*)commands_list->content;
		printf("command = %s$\n", command->command);
		while (*command->parameters != NULL)
			printf("parameter = %s$\n", *(command->parameters)++);
		commands_list = commands_list->next;
		printf("\n");
	}
}

int8_t	starting_processes(t_list *commands_list)
{
	int 		status;
	t_command	*command;

	while (commands_list)
	{
		command = (t_command*)commands_list->content;
		if (!ft_strcmp(command->command, "exit"))
			return (0);
		else if (fork())
			waitpid(-1, &status, 0);
		else
			status = execve(command->command, command->parameters, 0);
		commands_list = commands_list->next;
	}
	return (1);
}

int		main(void)
{
	int 		fd = open("test.txt", O_RDONLY);
	char		*user_input;
	t_list		*commands_list;

	while (TRUE)
	{
		type_prompt();
		get_next_line(1, &user_input);
		commands_list = get_commands_with_params_list(user_input);
		free(user_input);
		if (!starting_processes(commands_list))
			exit(0);
		free(commands_list);
	}
	return (0);
}
