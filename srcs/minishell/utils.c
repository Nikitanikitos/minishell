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

void	print_arguments_list(t_list	*commands)
{
	t_arguments	*command;

	while (commands)
	{
		printf("\n");
		command = (t_arguments*)commands->content;
		printf("command = %s$\n", command->command);
		while (*command->parameters != NULL)
			printf("parameter = %s$\n", *(command->parameters)++);
		commands = commands->next;
		printf("\n");
	}
}

void	type_prompt()
{
	static int	first_time = 1;

	if (first_time)
		write(STDOUT_FILENO, " \e[1:1H\e[2J", 12);
	first_time = 0;
	write(STDOUT_FILENO, "$", 1);
}

void	print_error(void)
{
	const char	*error[] = {"", "",
				  		"No such file or directory",
				  		"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
				  		"Is not a directory"};
	const int	error_length = ft_strlen(error[errno]);

	write(STDOUT_FILENO, error[errno], error_length);
	write(STDOUT_FILENO, "\n", 1);
}
