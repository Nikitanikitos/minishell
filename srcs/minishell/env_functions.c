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

t_list	*get_env_list(char **envp)
{
	t_env	*env;
	t_list	*env_list;
	char	**key_value;

	env_list = NULL;
	while (*envp)
	{
		key_value = ft_split(*envp, '=');
		if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
			return (NULL);
		env->key = key_value[0];
		env->value = key_value[1];
		if (env_list == NULL)
			env_list = ft_lstnew(env);
		else
			ft_lstadd_front(&env_list, ft_lstnew(env));
		envp++;
	}
	return (env_list);
}

