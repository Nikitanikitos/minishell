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

void	print_export(t_list *env_list)
{
	t_env	env;

	while (env_list)
	{
		env = *(t_env*)env_list->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env.key, 1);
		write(1, "=", 1);
		ft_putendl_fd(env.value, 1);
		env_list = env_list->next;
	}
}

int		export(void *arguments, t_list *env_list)
{
	const t_arguments	command = *(t_arguments*)arguments;

	if (!command.parameters[1])
		print_export(env_list);
	else if (ft_strchr(command.parameters[1], '='))
		add_env(ft_split(command.parameters[1], '='), &env_list);
	return (errno);
}
