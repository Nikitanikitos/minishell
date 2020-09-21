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
			{"env", NULL},
			{"exit", &ft_exit},
	};

	index = 0;
	while (index < NUMBER_BUILDIN_CMD)
	{
		if (!ft_strcmp(builtins[index].func_name, *(arguments.arguments)))
		{
			arguments.arguments++;
			if (builtins[index].func(&arguments, env_list))
				print_error();
			return (TRUE);
		}
		index++;
	}
	return (FALSE);
}

void	start_process(t_arguments *arguments, t_list *env_list)
{
	pid_t		pid;
	char		**env;
	int			status;

	errno = 0;
	if (execute_buildin_command(*arguments, env_list))
		;
	else if ((pid = fork()))
	{
		waitpid(-1, &status, 0);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		check_path(arguments->arguments, env_list);
		if ((status = execve(*arguments->arguments, arguments->arguments, NULL)))
		{
			print_error();
			exit(status);
		}
		close(arguments->fds.std_in);
	}
}

int 	get_pipe(t_fds *fds, int index)
{
	int 	fd[2];

	pipe(fd);
	dup2(fd[1], fds->std_in);
	dup2(fds->temp_fd, fds->std_out);
	dup2(fd[0], fds->std_out);
	return (index);
}

int		get_fd(t_list	*arguments, t_fds *fds)
{
	int		index;
	char 	*argument;

	index = 0;
	while (arguments)
	{
		argument = (char*)arguments->content;
		if (!ft_strcmp(argument, ">"))
			return (get_forward_redirect(arguments, index, fds));
		else if (!ft_strcmp(argument, ">>"))
			return (get_double_forward_redirect(arguments, index, fds));
		else if (!ft_strcmp(argument, "<"))
			return (get_back_redirect(arguments, index, fds) + 2);
		else if (!ft_strcmp(argument, "|"))
			return (index);
		arguments = arguments->next;
		index++;
	}
	return (index);
}

void	minishell(char *user_input, t_list *env_list)
{
	t_arguments	arguments;
	t_list		*arguments_list;
	pid_t		pid;
	int 		pipefd[2];
	int 		length;
	int 		index;
	int 		status;

	dup2(1, 3); // сохраненный 1 фд
	dup2(0, 4); //сохраненный 0 фд
	arguments.fds.std_in = 1;
	arguments.fds.std_out = 0;
	arguments.fds.temp_fd = 0;
	while (*user_input)
	{
		length = 0;
		if (*user_input == ';')
			user_input++;
		else
		{
			arguments_list = parse_user_input(user_input, &length, env_list);
			while (arguments_list)
			{
				index = get_fd(arguments_list, &arguments.fds);
				arguments.arguments = convert_from_list_to_array(arguments_list, index);
				move_list(&arguments_list, index + 1);
				pipe(pipefd);
				pid = fork();
				if (pid == 0)	// дочерний процесс
				{
					dup2(pipefd[0], STDIN_FILENO);
					close(pipefd[1]);
				}
				else			// родительский процесс
				{
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[0]);
					parse_arguments_in_command(&arguments.arguments, env_list);
					start_process(&arguments, env_list);
					waitpid(-1, &status, 0);
				}
			}
		}
		user_input += length;
	}
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
