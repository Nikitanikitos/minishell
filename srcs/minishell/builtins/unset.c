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

void	check_in_env(char *argument, t_list *env_list)
{
	t_list		*prev_element;
	t_env		*current_env;

	prev_element = NULL;
	while (env_list)
	{
		current_env = (t_env*)env_list->content;
		if (!ft_strcmp(current_env->key, argument))
		{
			unset_env(env_list, prev_element);
			return ;
		}
		prev_element = env_list;
		env_list = env_list->next;
	}
}

int		unset(t_arguments *arguments, t_list *env_list)
{
	if (!*arguments->arguments)
		return (errno);
	while (*arguments->arguments)
	{
		check_in_env(*arguments->arguments, env_list);
		arguments->arguments++;
	}
	return (errno);
}
