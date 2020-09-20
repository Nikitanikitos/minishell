/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <froxanne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:20:40 by froxanne          #+#    #+#             */
/*   Updated: 2020/09/20 15:34:37 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_forward_redirect(t_command *command, int index)
{
	int		fd;
	int		i;

	fd = 0;
	i = 0;
	while (command->arguments[i])
	{
		if (!ft_strncmp(">", command->arguments[i], 1))
		{
			index = i;
			if (fd != 0)
			{
				close(fd);
				fd = 0;
			}
			fd = open(command->arguments[++i], O_CREAT | O_APPEND | O_RDWR, 0777);
		}
		i++;
	}
	command->fd[1] = fd;
	return (index);
}

int		get_double_forward_redirect(t_command *command, int index)
{
	int		fd;
	int		i;

	fd = 0;
	i = 0;
	while (command->arguments[i])
	{
		if (!ft_strncmp(">>", command->arguments[i], 2))
		{
			index = i;
			if (fd != 0)
			{
				close(fd);
				fd = 0;
			}
			fd = open(command->arguments[++i], O_CREAT | O_TRUNC | O_RDWR, 0777);
		}
		i++;
	}
	command->fd[1] = fd;
	return (index);
}

int		get_back_redirect(t_command *command, int index)
{
	int		fd;
	int		i;

	fd = 0;
	i = 0;
	while (command->arguments[i])
	{
		if (!ft_strncmp("<", command->arguments[i], 1))
		{
			index = i;
			if (fd != 0)
			{
				close(fd);
				fd = 0;
			}
			fd = open(command->arguments[++i], O_RDONLY);
		}
		i++;
	}
	command->fd[0] = fd;
	return (index);
}
