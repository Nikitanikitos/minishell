/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <froxanne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:41:20 by imicah            #+#    #+#             */
/*   Updated: 2020/09/30 12:18:01 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "minishell.h"

int		execute_buildin_command(t_arguments arguments, t_list *env_list)
{
	int				index;
	const t_builtin	builtins[] = {
			{"echo", &echo},
			{"cd", &cd},
			{"pwd", &pwd},
			{"export", &export},
			{"unset", &unset},
			{"env", &env},
			{"exit", &ft_exit},
	};

	index = 0;
	while (index < NUMBER_BUILDIN_CMD)
	{
		if (!ft_strcmp(builtins[index].func_name, *(arguments.argv)))
		{
			arguments.argv++;
			if (builtins[index].func(&arguments, env_list))
				print_error(--arguments.argv);
			return (TRUE);
		}
		index++;
	}
	return (FALSE);
}

void	start_process(t_arguments *arguments, t_list *env_list)
{
	pid_t	pid;
	int		status;
	char	**env;

	errno = 0;
	g_status = 0;
	if (execute_buildin_command(*arguments, env_list))
		return ;
	env = convert_from_list_to_array(env_list);
	if ((pid = fork()))
	{
		wait(&status);
		check_exit_status(status);
		free_double_array(env);
		free(env);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		if (check_path(arguments->argv, env_list) == 0)
			execve(*arguments->argv, arguments->argv, env);
		exit_with_error(arguments);
	}
}

void	fork_process(t_arguments arguments, t_list *env_list)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(arguments.fds.std_write, STDOUT_FILENO);
		start_process(&arguments, env_list);
		close(arguments.fds.std_read);
		close(STDOUT_FILENO);
		exit(127);
	}
	else
	{
		dup2(arguments.fds.std_read, STDIN_FILENO);
		close(arguments.fds.std_write);
		wait(0);
		close(arguments.fds.std_read);
	}
}

void	minishell(char *user_input, t_list *env_list)
{
	t_arguments	arguments;

	while (*user_input)
	{
		if (*user_input == ';')
			user_input++;
		else
		{
			arguments_init(&arguments);
			arguments.argv = parse_user_input(&user_input,
					env_list, &arguments.fds);
			if (arguments.fds.std_read < 0 || arguments.fds.std_write < 0)
				ft_put_redirect_error(arguments.fds);
			else if (arguments.argv)
			{
				ft_lower(*arguments.argv);
				if (is_fork(arguments.fds))
					fork_process(arguments, env_list);
				else
					start_process(&arguments, env_list);
			}
			free_double_array(arguments.argv);
			free(arguments.argv);
		}
	}
}

int		main(int ac, char **av, char **envp)
{
	char	*user_input;
	t_list	*env_list;

	dup2(1, 3);
	dup2(0, 4);
	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, quit);
	if ((env_list = get_env_list(envp)) == NULL)
		exit(EXIT_FAILURE);
	while (TRUE)
	{
		type_prompt();
		dup2(4, 0);
		read_line(0, &user_input);
		if (user_input == NULL)
			eof_handler();
		else if (ft_put_error_pipe_colon(check_incorrect_pipe_colon(user_input)))
			printf("hello\n");
		else
			minishell(user_input, env_list);
		free(user_input);
	}
}
