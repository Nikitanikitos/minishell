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
#include "minishell.h"

void	print_command_and_parameters(char *command, char **parameters)
{
	printf("command = %s$\n", command);
	while (*parameters != NULL)
		printf("parameter = %s$\n", *(parameters)++);
}

int		main(int ac, char **av)
{
	char	command[100];
	char 	**parameters;
	int 	status;

	while (TRUE)
	{
		type_prompt();
		get_command_and_parameters(command, &parameters);
		print_command_and_parameters(command, parameters);
		if (fork())
			waitpid(-1, &status, 0);
		else
			execve(command, parameters, 0);
		if (command[0] == 'q')
			break;
	}
	return 0;
}
