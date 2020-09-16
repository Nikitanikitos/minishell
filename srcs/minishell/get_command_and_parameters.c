/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:12:06 by imicah            #+#    #+#             */
/*   Updated: 2020/09/02 20:12:07 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_commands_list(char **all_commands, t_list **arguments_list)
{
	t_arguments	*arguments;
	char		**command;

	while (*all_commands)
	{
		command = ft_split_advanced(*all_commands, " \t");
		arguments = arguments_init(command);
		if (!*arguments_list)
			*arguments_list = ft_lstnew(arguments);
		else
			ft_lstadd_back(arguments_list, ft_lstnew(arguments));
		all_commands++;
	}
}

t_list	*get_commands_list(char *user_input)
{
	char		**all_commands;
	t_list		*arguments_list;

	arguments_list = NULL;
	all_commands = ft_split_advanced(user_input, ";");
	parse_commands_list(all_commands, &arguments_list);
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
