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

int		echo(t_arguments *arguments, t_list *env_list)
{
	int		i;
	int		flag;

	flag = 1;
	i = 1;
	if (!ft_strcmp(arguments->parameters[1], "-n"))
	{
		i++;
		flag = 0;
	}
	while (arguments->parameters[i])
	{
		ft_putstr_fd(arguments->parameters[i], 1);
		i++;
		if (arguments->parameters[i])
			write(1, " ", 1);
	}
	write(STDOUT_FILENO, "\n", (size_t)flag);
	return (errno);
}
