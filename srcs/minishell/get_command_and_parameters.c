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

#include "minishell.h"

void	type_prompt()
{
	static int	first_time = 1;

	if (first_time)
		write(1, " \e[1:1H\e[2J", 12);
	first_time = 0;
	write(1, "$", 1);
}

void	parse_commands_list(char **all_commands_with_params, t_list **commands_with_params_list)
{
	t_command	command;
	char		**commands_with_params;

	while (*all_commands_with_params)
	{
		commands_with_params = ft_split(*all_commands_with_params, ' ');
		command.command = commands_with_params[0];
		command.parameters = commands_with_params;
		if (!*commands_with_params_list)
			*commands_with_params_list = ft_lstnew(&command);
		else
			ft_lstadd_back(commands_with_params_list, ft_lstnew(&command));
		all_commands_with_params++;
	}
}

t_list	*get_commands_with_params_list(char *user_input)
{
	t_list		*commands_with_params_list;
	char		**all_commands_with_params;

	commands_with_params_list = NULL;
	all_commands_with_params = ft_split(user_input, ';');
//	free(user_input);
	parse_commands_list(all_commands_with_params, &commands_with_params_list);
	return (commands_with_params_list);
}
