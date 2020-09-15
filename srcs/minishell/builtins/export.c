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

void	change_value_env(t_env *current_env, char **key_value)
{
	if (current_env->value && key_value[1] == NULL)
		free(key_value[1]);
	else
	{
		free(current_env->value);
		current_env->value = key_value[1];
	}
	free(key_value[0]);
}

void	change_or_add_value_env(char **key_value, t_list **env_list)
{
	t_list	*list_start = *env_list;
	t_env	*current_env;

	while ((*env_list)->next)
	{
		current_env = (t_env*)(*env_list)->content;
		if (!ft_strcmp(current_env->key, key_value[0]))
		{
			change_value_env(current_env, key_value);
			return ;
		}
		*env_list = (*env_list)->next;
	}
	current_env = (t_env*)(*env_list)->content;
	if (!ft_strcmp(current_env->key, key_value[0]))
		change_value_env(current_env, key_value);
	else
	{
		(*env_list)->next = ft_lstnew(env_init(key_value));
		*env_list = list_start;
	}
}

int		ft_str_double_len(char **array)
{
	int 	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int		export(void *arguments, t_list *env_list)
{
	const t_arguments	command = *(t_arguments*)arguments;
	char				**key_value;

	if (!command.parameters[1])
		print_export(env_list);
	else
	{
		key_value = ft_split(command.parameters[1], '=');
		if (ft_str_double_len(key_value) == 1)
		{
			if (ft_strchr(command.parameters[1], '='))
				key_value[1] = ft_strdup("");
		}
		change_or_add_value_env(key_value, &env_list);
	}
	return (errno);
}
