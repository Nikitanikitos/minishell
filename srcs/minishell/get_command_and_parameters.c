/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_with_params_list.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 20:12:06 by imicah            #+#    #+#             */
/*   Updated: 2020/09/02 20:12:07 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "minishell.h"

void	parse_commands_list(char **all_commands_with_params, t_list **commands_with_params_list)
{
	t_command	*command;
	char		**commands_with_params;

	while (*all_commands_with_params)
	{
		commands_with_params = ft_split(*all_commands_with_params, ' ');
		if (!(command = (t_command*)malloc(sizeof(t_command))))
			return ;
		command->command = commands_with_params[0];
		command->parameters = commands_with_params;
		if (!*commands_with_params_list)
			*commands_with_params_list = ft_lstnew(command);
		else
			ft_lstadd_back(commands_with_params_list, ft_lstnew(command));
		all_commands_with_params++;
	}
}

t_list	*get_commands_with_params_list(char *user_input)
{
	char		**all_commands_with_params;
	t_list		*commands_with_params_list;

	commands_with_params_list = NULL;
	all_commands_with_params = ft_split(user_input, ';');
	parse_commands_list(all_commands_with_params, &commands_with_params_list);
	free(all_commands_with_params);
	return (commands_with_params_list);
}

int		execute_command_in_buildins(t_command command)
{
	int				index;
	const t_builtin	builtins[] = {
			{"echo", NULL},
			{"cd", &cd},
			{"pwd", &pwd},
			{"export", NULL},
			{"unset", NULL},
			{"exit", &ft_exit},
	};

	index = 0;
	while (index < NUMBER_BUILDIN_CMD)
	{
		if (!ft_strcmp(builtins[index].command, command.command))
		{
			if (builtins[index].func(&command))
				print_error();
			return (TRUE);
		}
		index++;
	}
	return (FALSE);
}
