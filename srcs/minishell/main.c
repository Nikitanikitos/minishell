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
		if (!ft_strcmp(builtins[index].func_name, *(arguments.arguments)))
		{
			arguments.arguments++;
			if (builtins[index].func(&arguments, env_list))
				print_error(--arguments.arguments);
			return (TRUE);
		}
		index++;
	}
	return (FALSE);
}

void	start_process(t_arguments *arguments, t_list *env_list)
{
	pid_t		pid;
	int			status;

	errno = 0;
	if (execute_buildin_command(*arguments, env_list))
		;
	else if ((pid = fork()))
		wait(0);
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		check_path(arguments->arguments, env_list);
		if ((status = execve(*arguments->arguments, arguments->arguments, NULL)))
		{
			print_error(arguments->arguments);
			exit(status);
		}
	}
}

void	fork_process(t_arguments arguments, t_list *env_list)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)	// дочерний процесс
	{
		dup2(arguments.fds.std_out, STDOUT_FILENO);
		start_process(&arguments, env_list);
		close(arguments.fds.std_in);
		close(STDOUT_FILENO);
		exit(0);
	}
	else			// родительский процесс
	{
		dup2(arguments.fds.std_in, STDIN_FILENO);
		close(arguments.fds.std_out);
		wait(0);
		close(arguments.fds.std_in);
	}
}

void	minishell(char *user_input, t_list *env_list)
{
	t_arguments	arguments;
	t_list		*arguments_list;
	int			length;
	int			index;

	while (*user_input)
	{
		length = 0;
		if (*user_input == ';')
			user_input++;
		else
		{
			arguments_list = parse_user_input(user_input, &length);
			while (arguments_list)
			{
				index = get_fd(arguments_list, &arguments.fds);
				arguments.arguments = convert_from_list_to_array(arguments_list, index);
				parse_arguments_in_command(arguments.arguments, env_list);
				move_list(&arguments_list, index + 1);
				if (is_fork(arguments.fds))
					fork_process(arguments, env_list);
				else
					start_process(&arguments, env_list);
			}
		}
		user_input += length;
	}
}

int		main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_list		*env_list;

	dup2(1, 3);
	dup2(0, 4);
	signal(SIGINT, sigint_handler);
	if ((env_list = get_env_list(envp)) == NULL)
		exit(EXIT_FAILURE);
	while (TRUE)
	{
		type_prompt();
		get_next_line(4, &user_input);
		if (!*user_input)
			eof_handler();
		else if (*user_input == '\n')
			*user_input = 0;
		minishell(user_input, env_list);
		free(user_input);
	}
}
