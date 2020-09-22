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

int		get_forward_redirect(t_list *arguments, int index, t_fds *fds)
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
	return (index);
}

int		get_double_forward_redirect(t_list *arguments, int index, t_fds *fds)
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
	return (index);
}

int		get_back_redirect(t_list *arguments, int index, t_fds *fds)
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
	fds->std_in = fd; // TODO ?
	return (index);
}
