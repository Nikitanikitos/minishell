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


void	read_command(char command[], char *parameters[])
{
	int		q;

	q = 0;
	ft_bzero(command, 100);
	read(1, command, 100);
	while (command[q])
	{
		if (command[q] == '\n')
		{
			command[q] = 0;
			break;
		}
		q++;
	}
}

int		main(int ac, char **av)
{
	char	command[100] = "/bin/ls";
	char 	*parameters[] = {"/", NULL};
	int 	status;

	while (TRUE)
	{
		type_prompt();
		read_command(command, parameters);
		if (fork())
			waitpid(-1, &status, 0);
		else
			execve(command, parameters, 0);
		if (command[0] == 'q')
			break;
	}
	return 0;
}
