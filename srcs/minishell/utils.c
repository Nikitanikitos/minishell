/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 19:40:10 by imicah            #+#    #+#             */
/*   Updated: 2020/09/04 19:40:12 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_and_parameters(t_list	*commands_list)
{
	t_command	*command;

	while (commands_list)
	{
		printf("\n");
		command = (t_command*)commands_list->content;
		printf("command = %s$\n", command->command);
		while (*command->parameters != NULL)
			printf("parameter = %s$\n", *(command->parameters)++);
		commands_list = commands_list->next;
		printf("\n");
	}
}
