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

int		execute_buildin_command(t_command command, t_list *env_list)
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
		if (!ft_strcmp(builtins[index].command, *(command.arguments)))
		{
			command.arguments++;
			if (builtins[index].func(&command, env_list))
				print_error();
			return (TRUE);
		}
		index++;
	}
	return (FALSE);
}
void		print_double_array(char **array)
{
	while (*array != NULL)
		printf("%s\n", (*array)++);
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
		check_path(command->arguments, env_list);
		if ((status = execve(*(command->arguments), command->arguments, env)))
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

	while (*user_input)
	{
		length = 0;
		if (*user_input == ';')
			user_input++;
		else
		{
			command = parse_user_input(user_input, &length, env_list);
			start_process(command, env_list);
		}
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
