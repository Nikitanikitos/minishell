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

void	parse_commands_list(char **all_commands, t_list **arguments_list, t_list *env_list)
{
	t_arguments	*arguments;
	char		**command;
	int 		i;

	while (*all_commands)
	{
		i = 0;
		command = ft_split_advanced(*all_commands, " \t");
		while (command[i])
		{
			if (command[i][0] == '\"')
				command[i] = parse_argument_with_double_quotes(command[i], env_list);
			else if (command[i][0] == '\'')
				command[i] = parse_argument_with_single_quotes(command[i]);
			else if (ft_strchr(command[i], '$'))
				command[i] = parse_without_quotes(command[i], env_list);
			i++;
		}
		arguments = arguments_init(command);
		if (!*arguments_list)
			*arguments_list = ft_lstnew(arguments);
		else
			ft_lstadd_back(arguments_list, ft_lstnew(arguments));
		all_commands++;
	}
}

t_list	*get_commands_list(char *user_input, t_list *env_list)
{
	char		**all_commands;
	t_list		*arguments_list;

	arguments_list = NULL;
	all_commands = ft_split_advanced(user_input, ";");
	parse_commands_list(all_commands, &arguments_list, env_list);
	free_double_array(all_commands);
	return (arguments_list);
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
