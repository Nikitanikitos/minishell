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

int		get_pipe(t_fds *fds)
{
	int		fd[2];

	pipe(fd);
	fds->std_in = fd[0];
	fds->std_out = fd[1];
	return (1);
}

int		get_forward_redirect(char **arguments, t_fds *fds)
{
	int		fd;

	fd = 0;
	while (*arguments)
	{
		if (!ft_strcmp(">", *arguments))
		{
			free(*arguments);
			*arguments = NULL;
			arguments++;
			if (fd != 0)
				close(fd);
			fd = open(*arguments, O_CREAT | O_APPEND | O_RDWR, 0777);
		}
		arguments++;
	}
	fds->std_out = fd;
	return (1);
}

int		get_double_forward_redirect(char **arguments, t_fds *fds)
{
	int		fd;

	fd = 0;
	while (*arguments)
	{
		if (!ft_strcmp(">>", *arguments))
		{
			if (fd != 0)
				close(fd);
			fd = open(*arguments, O_CREAT | O_TRUNC | O_RDWR, 0777);
		}
		arguments++;
	}
	fds->std_out = fd;
	return (1);
}

int		get_back_redirect(char **arguments, t_fds *fds)
{
	int		fd;

	fd = 0;
	while (*arguments)
	{
		if (!ft_strcmp("<", *arguments))
		{
			if (fd != 0)
				close(fd);
			fd = open(*arguments, O_RDONLY);
		}
		arguments++;
	}
	fds->std_in = fd;
	return (1);
}

int		get_fd(char **arguments, t_fds *fds)
{
	int		index;
	int		next_index;

	fds->std_out = 4;
	fds->std_in = 3;
	index = 0;
	next_index = 0;
	while (arguments[index])
	{
		if (!ft_strcmp(arguments[index], ">"))
			next_index = get_forward_redirect(arguments + index, fds);
		else if (!ft_strcmp(arguments[index], ">>"))
			next_index = get_double_forward_redirect(arguments + index, fds);
		else if (!ft_strcmp(arguments[index], "<"))
			next_index = get_back_redirect(arguments + index, fds);
		else if (!ft_strcmp(arguments[index], "|"))
		{
			next_index = get_pipe(fds);
			break ;
		}
		index += (next_index) ? next_index : 1;
	}
	if (arguments[index])
		free(arguments[index]);
	arguments[index] = NULL;
	return (index + next_index);
}
