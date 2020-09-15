/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:29:09 by imicah            #+#    #+#             */
/*   Updated: 2020/09/15 20:29:10 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

int		unset(t_arguments *arguments, t_list *env_list)
{
	t_list		*temp_elem;
	t_list		*prev_element;
	t_env		*current_env;

	prev_element = NULL;
	if (!arguments->parameters[1])
		return (errno);
	while (env_list)
	{
		current_env = (t_env*)env_list->content;
		if (!ft_strcmp(current_env->key, arguments->parameters[1]))
		{
			free_env(env_list->content);
			if (prev_element)
			{
				prev_element->next = env_list->next;
				free(env_list);
			}
			else if (env_list->next)
			{
				temp_elem = env_list;
				env_list = env_list->next;
				free(temp_elem);
			}
			return (errno);
		}
		prev_element = env_list;
		env_list = env_list->next;
	}
	return (errno);
}
