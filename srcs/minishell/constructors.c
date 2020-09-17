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

t_arguments	*arguments_init(char **command)
{
	t_arguments	*arguments;

	if (!(arguments = (t_arguments*)malloc(sizeof(t_arguments))))
		return (NULL);
	arguments->command = command[0];
	arguments->parameters = command;
	return (arguments);
}

t_env	*env_init(char **key_value)
{
	t_env	*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		return (NULL);
//	env->key = ft_strdup(key_value[0]);
//	env->value = ft_strdup(key_value[1]);
	env->key = key_value[0];
	env->value = key_value[1];
	return (env);
}
