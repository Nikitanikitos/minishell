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
	if (*arguments->arguments && !ft_strcmp(*(arguments->arguments), "-n"))
	{
		flag = 0;
		arguments->arguments++;
	}
	while (*(arguments->arguments))
	{
		ft_putstr_fd(*(arguments->arguments)++, 1);
		if (*(arguments->arguments))
			write(1, " ", 1);
	}
	write(1, "\n", (size_t)flag);
	return (errno);
}
