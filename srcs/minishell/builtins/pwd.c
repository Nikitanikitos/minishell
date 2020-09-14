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

void	cd(void *command)
{

	char	*new_path;
	char	*cwd;

//	if ((char*)path[0] == '/')
//		chdir(path);
//	else if
//	{
		cwd = getcwd(NULL, 0);
		new_path = ft_strjoin(cwd, path);
		free(path);
		free(cwd);
		chdir(new_path);
//	}
}

void	ft_exit(void* q)
{
	exit(0);
}