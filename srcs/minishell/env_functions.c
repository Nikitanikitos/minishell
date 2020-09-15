/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 21:31:03 by imicah            #+#    #+#             */
/*   Updated: 2020/09/14 21:31:03 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char **key_value, t_list **env_list)
{
	t_env	*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		return ;
	env->value = key_value[0];
	env->key = (key_value[1]) ? key_value[1] : ft_strdup("");
	ft_lstadd_back(env_list, ft_lstnew(env));
}

t_env	*env_init(char **key_value)
{
	t_env	*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		return (NULL);
	env->key = key_value[0];
	env->value = key_value[1];
	return (env);
}

t_list	*get_env_list(char **envp)
{
	t_env	*env;
	t_list	*start_list;
	t_list	*env_list;

	env_list = NULL;
	start_list = NULL;
	while (*envp)
	{
		env = env_init(ft_split(*envp, '='));
		if (env_list == NULL)
		{
			env_list = ft_lstnew(env);
			start_list = env_list;
		}
		else
		{
			env_list->next = ft_lstnew(env);
			env_list = env_list->next;
		}
		envp++;
	}
	return (start_list);
}
