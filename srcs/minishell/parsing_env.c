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

char	*parse_with_envp(char *parameters, t_list *env_list)
{
	char	*result;
	char	*temp;
	int		index;

	if (*parameters == '$')
	{
		result = ft_strdup(get_env_value(parameters, env_list));
		free(parameters);
	}
	else
	{
		index = str_get_index(parameters, "$");
		result = ft_strndup(parameters, (size_t)index);
		parameters += index;
		temp = result;
		result = ft_strjoin(result, get_env_value(parameters, env_list));
		free(temp);
	}
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
		command = ft_strjoin((*paths)++, current_command);
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
	int			i;
	int			fd;

	i = 0;
	if ((fd = open(*command, O_RDONLY)) != -1)
		return (close(fd));
	current_command = ft_strjoin("/", *command);
	free(*command);
	if ((paths = get_paths(env_list)) == NULL)
	{
		free(current_command);
		return (1);
	}
	*command = get_current_path(paths, current_command, *command);
	if (*command == NULL)
		*command = (char*)temp_command;
	free_double_array(paths);
	free(paths); // TODO чекнуть на маке
	free(current_command);
	return (0);
}
