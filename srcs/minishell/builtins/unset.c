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

int		unset(t_arguments *command, t_list *env_list)
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

void	delete_element(t_list *list, t_list *prev_element)
{
	t_list *temp_element;

	free_env(list->content);
	if (prev_element)
	{
		prev_element->next = list->next;
		free(list);
	}
	else if (list->next)
	{
		temp_element = list->next;
		list->content = list->next->content;
		list->next = list->next->next;
		free(temp_element);
	}
}

void	move_list(t_list **list, int length)
{
	t_list *temp_element;

	while (list && length--)
	{
		temp_element = *list;
		if (temp_element == NULL)
			return;
		*list = (*list)->next;
		free(temp_element->content);
		free(temp_element);
	}
}
