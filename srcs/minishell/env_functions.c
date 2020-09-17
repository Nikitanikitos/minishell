/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 01:34:32 by imicah            #+#    #+#             */
/*   Updated: 2020/09/17 11:07:19 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *key, t_list *env_list)
{
	t_env	*env;

	key++;
	while (env_list)
	{
		env = (t_env*)env_list->content;
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env_list = env_list->next;
	}
	return ("");
}

void	change_value_env(t_env *current_env, t_env *env)
{
	if (current_env->value && env->value == NULL)
		free(env->value);
	else
	{
		free(current_env->value);
		current_env->value = env->value;
	}
	free(env->key);
	free(env);
}

void	list_element_swap(t_list *first_element, t_list *second_element)
{
	void	*temp_content;

	temp_content = first_element->content;
	first_element->content = second_element->content;
	second_element->content = temp_content;
}

void	add_env(t_list *env_list, t_env *env)
{
	t_list	*temp_elem;
	t_env	*current_env;
	int		compare_result;

	while (env_list)
	{
		current_env = (t_env*)env_list->content;
		compare_result = ft_strcmp(env->key, current_env->key);
		if (compare_result <= 0 || env_list->next == NULL)
		{
			if (compare_result < 0)
			{
				temp_elem = env_list->next;
				env_list->next = ft_lstnew(env);
				if (temp_elem)
					env_list->next->next = temp_elem;
				list_element_swap(env_list, env_list->next);
			}
			else if (compare_result == 0)
				change_value_env(current_env, env);
			else
				env_list->next = ft_lstnew(env);
			break ;
		}
		env_list = env_list->next;
	}
}

t_list	*get_env_list(char **envp)
{
	char	**key_value;
	t_env	*env;
	t_list	*env_list;

	env_list = NULL;
	while (*envp)
	{
		key_value = ft_split(*envp, '=');
		env = env_init(key_value);
		free_double_array(key_value);
		key_value = NULL;
		if (!env_list)
			env_list = ft_lstnew(env);
		else
			add_env(env_list, env);
		envp++;
	}
	return (env_list);
}
