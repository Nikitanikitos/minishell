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

int		pwd(void* q)
{
	char	*cwd = getcwd(NULL, 0);
	const int	length = ft_strlen(cwd);

	write(1, cwd, length);
	free(cwd);
	write(1, "\n", 1);
	return (errno);
}

char	*get_destination_directory(char *directory)
{
	char	*new_path;
	char 	*temp_path;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	temp_path = ft_strjoin("/", directory);
	new_path = ft_strjoin(cwd, temp_path);
	free(temp_path);
	free(cwd);
	return (new_path);
}

int		cd(void *arguments)
{
	const	t_arguments command = *(t_arguments*)arguments;
	char	*new_path;

	if (command.parameters[1] == NULL)
		new_path = ft_strdup("/");
	else if (command.parameters[1][0] == '/' ||
		!ft_strncmp(command.parameters[1], "../", 3))
		new_path = ft_strdup(command.parameters[1]);
	else
		new_path = get_destination_directory(command.parameters[1]);
	chdir(new_path);
	free(new_path);
	return (errno);
}

int	ft_exit(void* q)
{
	exit(0);
}
