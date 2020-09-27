/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:01:58 by imicah            #+#    #+#             */
/*   Updated: 2020/09/17 11:06:12 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_init(char **key_value)
{
	t_env	*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		return (NULL);
	env->key = key_value[0];
	env->value = key_value[1];
	return (env);
}

void	free_double_array(char **array)
{
	char	*temp;

	while (*array)
	{
		temp = *array;
		array++;
		free(temp);
	}
}

void	free_env(void *arg)
{
	t_env *env;

	env = (t_env*)arg;
	free(env->value);
	free(env->key);
	free(env);
}

void	arguments_init(t_arguments *arguments)
{
	arguments->fds.back_redirect = 0;
	arguments->fds.fork = 0;
	arguments->fds.std_read = 4;
	arguments->fds.std_write = 3;
}
