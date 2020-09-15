/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                            	    +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 21:31:03 by imicah            #+#    #+#             */
/*   Updated: 2020/09/14 21:31:03 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_list	*get_env_list(char **envp)
{
	t_env	*env;
	t_list	*start_list;
	t_list	*env_list;

	env = env_init(ft_split(*envp++, '='));
	env_list = ft_lstnew(env);
	start_list = env_list;
	while (*envp)
	{
		env = env_init(ft_split(*envp, '='));
		env_list->next = ft_lstnew(env);
		env_list = env_list->next;
		envp++;
	}
	return (start_list);
}
