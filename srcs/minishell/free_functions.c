/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:52:25 by imicah            #+#    #+#             */
/*   Updated: 2020/09/17 11:04:04 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_array(char **array)
{
	char	*temp;

	while (*array)
	{
		temp = *array;
		array++;
		free(temp);
	}
//	free(array);
}

//void	free_arguments(void *arguments)
//{
//	t_arguments *commands;
//
//	commands = (t_arguments*)arguments;
//	free_double_array(commands->parameters);
//	free(commands);
//}

void	free_env(void *arg)
{
	t_env *env;

	env = (t_env*)arg;
	free(env->value);
	free(env->key);
	free(env);
}
