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

void	change_value_env(t_env *current_env, char **key_value)
{
		free(current_env->value);
		current_env->value = key_value[1];
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

int		export(void *arguments, t_list *env_list)
{
	const t_arguments	command = *(t_arguments*)arguments;
	char				**env_without_value;

	if (!command.parameters[1])
		print_export(env_list);
	else
		change_or_add_value_env(ft_split(command.parameters[1], '='), &env_list);
//	else if (ft_strchr(command.parameters[1], '='))
//		add_env(ft_split(command.parameters[1], '='), &env_list);
//	else
//	{
//		if ((env_without_value = (char**)malloc(sizeof(char*))) == NULL)
//			return (0);
//		env_without_value[0] = command.parameters[1];
//		env_without_value[1] = NULL;
//		add_env(env_without_value, &env_list);
//	}
	return (errno);
}
