/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:41:20 by imicah            #+#    #+#             */
/*   Updated: 2020/09/02 15:41:22 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	check_path(char **command, t_list *env_list)
{
	char	*temp_command;
	char 	**paths;
	int 	i;
	int 	fd;

	i = 0;
	if ((fd = open(*command, O_RDONLY)) != -1)
	{
		close(fd);
		return;
	}
	temp_command = ft_strjoin("/", *command);
	free(*command);
	if ((paths = get_paths(env_list)) == NULL)
		return;
	while (paths[i])
	{
		*command = ft_strjoin(paths[i], temp_command);
		if ((fd = open(*command, O_RDONLY)) != -1)
			break;
		free(*command);
		i++;
	}
	if (fd != -1)
		close(fd);
	free_double_array(paths);
}

void	starting_processes(t_list *command_list, t_list *env_list)
{
	pid_t		pid;
	char		**env;
	int			status;
	t_arguments	*arguments;

	while (command_list)
	{
		errno = 0;
		arguments = (t_arguments*)command_list->content;
		if (execute_buildin_command(*arguments, env_list))
		{
		}
		else if ((pid = fork()))
			waitpid(-1, &status, 0);
		else if (pid < 0)
			exit(EXIT_FAILURE);
		else
		{
			check_path(&arguments->command, env_list);
			if ((status = execve(arguments->command, arguments->parameters, env)))
			{
				print_error();
				exit(status);
			}
		}
		command_list = command_list->next;
	}
}

int		main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_list		*commands_list;
	t_list		*env_list;

	if ((env_list = get_env_list(envp)) == NULL)
		exit(1);
	while (TRUE)
	{
		type_prompt();
		get_next_line(0, &user_input);
		commands_list = get_commands_list(user_input);
		free(user_input);
		starting_processes(commands_list, env_list);
		ft_lstclear(commands_list, &free_arguments);
	}
}
