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

void	print_env(char *env_key, t_list *env_list)
{
	t_env	*env;

	env_key++;
	while (env_list)
	{
		env = (t_env*)env_list->content;
		if (!ft_strcmp(env->key, env_key))
		{
			ft_putstr_fd(env->value, 1);
			break ;
		}
		env_list = env_list->next;
	}
}

int		echo(t_arguments *arguments, t_list *env_list)
{
	int					i;
	int					flag;

	flag = 1;
	i = 1;
	if (!ft_strcmp(arguments->parameters[1], "-n"))
	{
		i++;
		flag = 0;
	}
	while (arguments->parameters[i])
	{
		if (arguments->parameters[i][0] == '$')
			print_env(arguments->parameters[i], env_list);
		else
			ft_putstr_fd(arguments->parameters[i], 1);
		i++;
		if (arguments->parameters[i])
			write(1, " ", 1);
	}
	write(STDOUT_FILENO, "\n", (size_t)flag);
	return (errno);
}
