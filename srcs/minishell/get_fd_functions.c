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

void	get_pipe_fd(char **arguments, t_fds *fds)
{
	int		fd[2];

	pipe(fd);
	(*arguments)++;
	fds->std_in = fd[0];
	fds->std_out = fd[1];
}

int		get_forward_redirect(char **arguments, t_fds *fds)
{
	char	*temp_arguments;
	char	temp_chr;
	int		fd;
	int 	length;

	fd = 0;
	length = 0;
	temp_arguments = *arguments;
	while (*temp_arguments)
	{
		if (!ft_strncmp(">", temp_arguments, 1))
		{
			temp_arguments++;
			if (fd != 0)
				close(fd);
			while (!ft_isspace(temp_arguments[length]))
				length++;
			temp_chr = temp_arguments[length];
			temp_arguments[length] = 0;
			fd = open(temp_arguments, O_CREAT | O_APPEND | O_RDWR, 0777);
			temp_arguments[length] = temp_chr;
		}
		arguments++;
	}
	*arguments = temp_arguments;
	fds->std_out = fd;
	return (1);
}

int		get_double_forward_redirect(char **arguments, t_fds *fds)
{
	int		fd;

	fd = 0;
	while (*arguments)
	{
		if (!ft_strncmp(">>", *arguments, 2))
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
		if (!ft_strncmp("<", *arguments, 1))
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

int		get_redirect_fd(char **arguments, t_fds *fds)
{
	char	*temp_arguments;

	temp_arguments = *arguments;
	while (*temp_arguments)
	{
		if (!ft_strncmp(temp_arguments, ">", 1))
			get_forward_redirect(&temp_arguments, fds);
		else if (!ft_strncmp(temp_arguments, ">>", 2))
			get_double_forward_redirect(&temp_arguments, fds);
		else if (!ft_strncmp(temp_arguments, "<", 1))
			get_back_redirect(&temp_arguments, fds);
	}
	return (0);
}
