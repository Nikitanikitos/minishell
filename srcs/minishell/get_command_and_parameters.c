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

void	parse_arguments_in_command(char **command, t_list *env_list)
{
	while (*command)
	{
		if ((*command)[0] == '\"')
			*command = parse_argument_with_double_quotes(*command, env_list);
		else if ((*command)[0] == '\'')
			*command = parse_argument_with_single_quotes(*command);
		else if (ft_strchr(*command, '$'))
			*command = parse_with_envp(*command, env_list);
		command++;
	}
}

t_command	*parse_user_input(char *user_input, int *length, t_list *env_list)
{
	t_list		*arguments_list;
	char		**arguments_array;

	arguments_list = parse(user_input, length);
	arguments_array = convert_from_list_to_array(arguments_list);
//	ft_lstclear(arguments_list, &free);
	parse_arguments_in_command(arguments_array, env_list);
	return (arguments_init(arguments_array));
}

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
