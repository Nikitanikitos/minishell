/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:40:22 by imicah            #+#    #+#             */
/*   Updated: 2020/09/14 12:40:24 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void* q)
{
	char	*cwd = getcwd(NULL, 0);
	const int	length = ft_strlen(cwd);

	write(1, cwd, length);
	free(cwd);
	write(1, "\n", 1);
}

void	cd(void *commandd)
{
	const	t_command command = *(t_command*)commandd;
	char	*new_path;
	const char	*cwd = getcwd(NULL, 0);

	if (command.parameters[1][0] == '/')
		chdir(command.parameters[1]);
	else
	{
		new_path = ft_strjoin("/", command.parameters[1]);
		free(command.parameters[1]);
		command.parameters[1] = new_path;
		new_path = ft_strjoin(cwd, command.parameters[1]);
		free(command.parameters[1]);
	}
	chdir(new_path);
	free(new_path);
}

void	ft_exit(void* q)
{
	exit(0);
}