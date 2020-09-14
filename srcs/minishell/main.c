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

int8_t	starting_processes(t_list *command_list)
{
	pid_t		pid;
	int			status;
	t_arguments	*arguments;

	while (command_list)
	{
		errno = 0;
		arguments = (t_arguments*)command_list->content;
		if (execute_command_in_buildins(*arguments))
		{
		}
		else if ((pid = fork()))
			waitpid(-1, &status, 0);
		else if (pid < 0)
			exit(EXIT_FAILURE);
		else
			status = execve(arguments->command, arguments->parameters, 0);
		command_list = command_list->next;
	}
	return (TRUE);
}

int		main(void)
{
	char		*user_input;
	t_list		*commands_list;

	//	int 		fd = open("test.txt", O_RDONLY);
	while (TRUE)
	{
		type_prompt();
		get_next_line(0, &user_input);
		commands_list = get_commands_list(user_input);
		free(user_input);
		starting_processes(commands_list);
		free_list(commands_list);
	}
}
