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

void	unset_env(t_list *env_list, t_list *prev_element)
{
	t_list *temp_element;

	free_env(env_list->content);
	if (prev_element)
	{
		prev_element->next = env_list->next;
		free(env_list);
	}
	else if (env_list->next)
	{
		temp_element = env_list->next;
		env_list->content = env_list->next->content;
		env_list->next = env_list->next->next;
		free(temp_element);
	}
}

int		unset(t_command *command, t_list *env_list)
{
	t_list		*prev_element;
	t_env		*current_env;

	prev_element = NULL;
	if (!*(command->arguments))
		return (errno);
	while (env_list)
	{
		current_env = (t_env*)env_list->content;
		if (!ft_strcmp(current_env->key, *(command->arguments)))
		{
			unset_env(env_list, prev_element);
			return (errno);
		}
		prev_element = env_list;
		env_list = env_list->next;
	}
	return (errno);
}
