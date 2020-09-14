/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 20:20:23 by imicah            #+#    #+#             */
/*   Updated: 2020/09/14 20:20:24 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env()
{
	int i;

	i = 0;
	while (__environ[i])
		ft_putendl_fd(__environ[i++], 1);
}

int		export(void *arguments)
{
	const t_arguments	command = *(t_arguments*)arguments;
	int i = 0;

	if (!command.parameters[1])
		print_env();
	while (__environ[i])
	{
		printf("%s\n", __environ[i]);
		i++;
	}
	return (errno);
}
