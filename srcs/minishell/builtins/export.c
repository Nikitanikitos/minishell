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
		if (env.value)
		{
			write(1, "=", 1);
			if (*(env.value))
				ft_putendl_fd(env.value, 1);
			else
				ft_putendl_fd("\'\'", 1);
		}
		else
			write(1, "\n", 1);
		env_list = env_list->next;
	}
}

int		export(t_arguments	*arguments, t_list *env_list)
{
	char				**key_value;

	if (!arguments->parameters[1])
		print_export(env_list);
	else
	{
		key_value = ft_split(arguments->parameters[1], '=');
		if (ft_str_double_len(key_value) == 1)
		{
			if (ft_strchr(arguments->parameters[1], '='))
				key_value[1] = ft_strdup("");
		}
		add_env(env_list, env_init(key_value));
	}
	return (errno);
}
