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
			ft_putendl_fd(env.value, 1);
		}
		else
			write(1, "\n", 1);
		env_list = env_list->next;
	}
}

int		valid_export_key(char *key)
{
	if (ft_atoi(key))
		return (0);
	while (*key)
		if (ft_isalnum(*key++) && *key != '_')
			return (1);
	return (0);
}

void	export_error(char **key_value)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(key_value[0], 2);
	ft_putstr_fd("': not valid identifier\n", 2);
	free(key_value[0]);
	if (key_value[1])
		free(key_value[1]);
}

int		export(t_arguments *arguments, t_list *env_list)
{
	char	**key_value;

	if (!*(arguments->argv))
		print_export(env_list);
	else
	{
		while (*arguments->argv)
		{
			key_value = ft_split(*arguments->argv, '=');
			if (!valid_export_key(key_value[0]))
			{
				export_error(key_value);
				return (errno);
			}
			if (ft_str_double_len(key_value) == 1)
			{
				if (ft_strchr(*arguments->argv, '='))
					key_value[1] = ft_strdup("\'\'");
			}
			add_env(env_list, env_init(key_value));
			free(key_value);
			arguments->argv++;
		}
	}
	return (errno);
}

int		env(t_arguments *arguments, t_list *env_list)
{
	t_env	env;

	(void)arguments;
	while (env_list)
	{
		env = *(t_env*)env_list->content;
		if (env.value)
		{
			ft_putstr_fd(env.key, 1);
			write(1, "=", 1);
			ft_putendl_fd(env.value, 1);
		}
		env_list = env_list->next;
	}
	return (errno);
}
