/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_and_parameters.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:12:06 by imicah            #+#    #+#             */
/*   Updated: 2020/09/17 11:24:55 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO ' и " кавычки без разделений не работают

void	parse_arguments_in_command(char **command, t_list *env_list)
{
	while (*command)
	{
		if ((*command)[0] == '\"')
			*command = parse_argument_with_double_quotes(*command, env_list);
		if ((*command)[0] == '\'')
			*command = parse_argument_with_single_quotes(*command);
		if (ft_strchr(*command, '$'))
			*command = parse_with_envp(*command, env_list);
		command++;
	}
}

void	parse_and_execute_command(char **commands, t_list *env_list)
{
	t_arguments	*arguments;
	char		**command;

	while (*commands)
	{
		command = ft_split_advanced(*commands, " \t");
		parse_arguments_in_command(command, env_list);
		arguments = arguments_init(command);
		start_process(arguments, env_list);
		free_arguments(arguments);
		commands++;
	}
}

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
		if (!ft_strcmp(builtins[index].command, arguments.command))
		{
			if (builtins[index].func(&arguments, env_list))
				print_error();
			return (TRUE);
		}
		index++;
	}
	return (FALSE);
}
