/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 21:22:29 by imicah            #+#    #+#             */
/*   Updated: 2020/09/16 21:22:31 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_with_envp(char **argument, t_list *env_list)
{
	char		*temp_argument;
	char		*result;
	char		temp_symbol;
	int 		i;

	i = 0;
	(*argument)++;
	temp_argument = *argument;
	while (temp_argument[i] && !ft_isspace(temp_argument [i]) &&
			temp_argument[i] != '$' && temp_argument[i] != '\\')
		i++;
	temp_symbol = temp_argument[i];
	temp_argument[i] = 0;
	result = ft_strdup(get_env_value(temp_argument, env_list));
	temp_argument[i] = temp_symbol;
	temp_argument += i;
	*argument = temp_argument;
	return (result);
}

char	**get_paths(t_list *env_list)
{
	t_env	*env;

	while (env_list)
	{
		env = (t_env*)env_list->content;
		if (!ft_strcmp(env->key, "PATH"))
			return (ft_split(env->value, ':'));
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_current_path(char **paths, char *current_command, char *command)
{
	int 	fd;

	while (*paths)
	{
		command = ft_strjoin(*paths++, current_command);
		if ((fd = open(command, O_RDONLY)) != -1)
			break ;
		free(command);
		command = NULL;
	}
	if (fd != -1)
		close(fd);
	return (command);
}

int 	check_path(char **command, t_list *env_list)
{
	const char	*temp_command = ft_strdup(*command);
	char		*current_command;
	char		**paths;
	int			fd;

	current_command = ft_strjoin("/", *command);
	free(*command);
	if ((paths = get_paths(env_list)) == NULL)
		free(current_command);
	else if ((*command = get_current_path(paths, current_command, *command)))
	{
		free(current_command);
		free_double_array(paths);
		free(paths); // TODO чекнуть на маке
		return (0);
	}
	if ((fd = open(temp_command, O_RDONLY)) != -1)
	{
		*command = (char*)temp_command;
		close(fd);
	}
	else
		*command = (char*)temp_command;
	return (0);
}
