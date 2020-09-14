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

#include "minishell.h"

int8_t	starting_processes(t_list *commands_list)
{
	pid_t		pid;
	int 		status;
	t_command	*command;

	while (commands_list)
	{
		errno = 0;
		command = (t_command*)commands_list->content;
		if (execute_command_in_buildins(*command))
		{}
		else if ((pid = fork()))
			waitpid(-1, &status, 0);
		else if (pid < 0)
			exit(1);
		else
			status = execve(command->command, command->parameters, 0);
		commands_list = commands_list->next;
	}
	return (TRUE);
}

int		main(void)
{
//	int 		fd = open("test.txt", O_RDONLY);
	char		*user_input;
	t_list		*commands_list;

	while (TRUE)
	{
		type_prompt();
		get_next_line(0, &user_input);
		commands_list = get_commands_with_params_list(user_input);
		free(user_input);
		starting_processes(commands_list);
		free(commands_list);
	}
}
