/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:13:01 by imicah            #+#    #+#             */
/*   Updated: 2020/09/14 17:13:02 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(void *arguments)
{
	int					i;
	int					flag;
	const t_arguments	command = *(t_arguments*)arguments;

	flag = 1;
	i = 1;
	if (!ft_strcmp(command.parameters[1], "-n"))
	{
		i++;
		flag = 0;
	}
	while (command.parameters[i])
	{
		write(1, command.parameters[i], ft_strlen(command.parameters[i]));
		i++;
		if (command.parameters[i])
			write(1, " ", 1);
	}
	write(STDOUT_FILENO, "\n", flag);
	return (errno);
}
