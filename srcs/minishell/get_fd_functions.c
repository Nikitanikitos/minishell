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

void	get_pipe(t_fds *fds)
{
	int		fd[2];

	pipe(fd);
	fds->std_in = fd[0];
	fds->std_out = fd[1];
}

void	get_forward_redirect(t_list *arguments, t_fds *fds)
{
	int		fd;

	fd = 0;
	while (arguments)
	{
		if (!ft_strcmp(">", (char*)arguments->content))
		{
			if (fd != 0)
				close(fd);
			fd = open((char*)arguments->next->content, O_CREAT | O_APPEND | O_RDWR, 0777);
		}
		arguments = arguments->next;
	}
	fds->std_out = fd;
}

void	get_double_forward_redirect(t_list *arguments, t_fds *fds)
{
	int		fd;

	fd = 0;
	while (arguments)
	{
		if (!ft_strcmp(">>", (char*)arguments->content))
		{
			if (fd != 0)
				close(fd);
			fd = open((char*)arguments->next->content, O_CREAT | O_TRUNC | O_RDWR, 0777);
		}
		arguments = arguments->next;
	}
	fds->std_out = fd;
}

void	get_back_redirect(t_list *arguments, t_fds *fds)
{
	int		fd;

	fd = 0;
	while (arguments)
	{
		if (!ft_strcmp("<", (char*)arguments->content))
		{
			if (fd != 0)
				close(fd);
			fd = open((char*)arguments->next->content, O_RDONLY);
		}
		arguments = arguments->next;
	}
	fds->std_in = fd;
}

int		get_fd(char **arguments, t_fds *fds)
{
	while (arguments)
	{
		if (!ft_strcmp(*arguments, ">"))
			get_forward_redirect(arguments, fds);
		else if (!ft_strcmp(*arguments, ">>"))
			get_double_forward_redirect(arguments, fds);
		else if (!ft_strcmp(*arguments, "<"))
			get_back_redirect(arguments, fds);
		else if (!ft_strcmp(*arguments, "|"))
		{
			get_pipe(fds);
			break ;
		}
		arguments++;
	}
	return (index);
}
