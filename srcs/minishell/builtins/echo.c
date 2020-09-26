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
	int		flag;

	flag = 1;
	if (*arguments->argv && !ft_strcmp(*(arguments->argv), "-n"))
	{
		flag = 0;
		arguments->argv++;
	}
	while (*(arguments->argv))
	{
		ft_putstr_fd(*(arguments->argv)++, 1);
		if (*(arguments->argv))
			write(1, " ", 1);
	}
	write(1, "\n", (size_t)flag);
	return (errno);
}
