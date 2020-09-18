/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:41:20 by imicah            #+#    #+#             */
/*   Updated: 2020/09/17 11:31:25 by froxanne         ###   ########.fr       */
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

void	start_process(t_command *command, t_list *env_list)
{
	pid_t		pid;
	char		**env;
	int			status;

	errno = 0;
	if (execute_buildin_command(*command, env_list))
		;
	else if ((pid = fork()))
		waitpid(-1, &status, 0);
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		check_path(&(command->arguments[0]), env_list);
		if ((status = execve(command->arguments[0], command->arguments, env)))
		{
			print_error();
			exit(status);
		}
	}
}

t_list	*minishell(char *user_input, t_list *env_list)
{
	t_command	*command;
	int 		length;

	length = 0;
	while (*user_input)
	{
		command = parse_user_input(user_input, &length, env_list);
		start_process(command, env_list);
		user_input += length;
	}
	return (NULL);
}

int		main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_list		*env_list;

	signal(SIGINT, sigint_handler); // TODO добить сигналы
	if ((env_list = get_env_list(envp)) == NULL)
		exit(1);
	while (TRUE)
	{
		type_prompt();
		get_next_line(0, &user_input);
		if (!*user_input)
			eof_handler();
		else if (*user_input == '\n')
			*user_input = 0;
		minishell(user_input, env_list);
		free(user_input);
	}
	return (0);
}
