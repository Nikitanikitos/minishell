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
	char	*temp_argument;
	char	*result;
	char	temp_symbol;
	int		i;

	i = 0;
	(*argument)++;
	temp_argument = *argument;
	while (temp_argument[i] && !ft_isspace(temp_argument[i]) &&
			!ft_strchr("$\'\"\\=|;><", temp_argument[i]))
		i++;
	temp_symbol = temp_argument[i];
	temp_argument[i] = 0;
	if (!ft_strcmp(temp_argument, "?"))
		result = ft_itoa(g_status);
	else if (!i)
		result = ft_strdup("$");
	else
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
	int		fd;

	fd = 0;
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

int		check_absolute_path(const char *s)
{
	return (!ft_strncmp("../", s, 3) ||
			!ft_strncmp("/", s, 1) || !ft_strncmp("./", s, 2));
}

int		check_path(char **command, t_list *env_list)
{
	char		*temp_command;
	char		*current_command;
	char		**paths;
	int			fd;

	if (!**command || check_absolute_path(*command))
		return (((fd = open(*command, O_RDONLY)) == -1) ? 1 : close(fd));
	temp_command = ft_strdup(*command);
	if ((paths = get_paths(env_list)))
	{
		current_command = ft_strjoin("/", temp_command);
		*command = get_current_path(paths, current_command, *command);
		free_double_array(paths);
		free(paths);
		free(current_command);
	}
	if (*command == NULL)
	{
		errno = 0;
		*command = temp_command;
		return (1);
	}
	free(temp_command);
	return (0);
}
