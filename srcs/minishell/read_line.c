/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <froxanne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 16:14:56 by froxanne          #+#    #+#             */
/*   Updated: 2020/09/29 13:03:33 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_line(int fd, char **line)
{
	char	buf[2];
	char	*tmp;
	char	*result;

	buf[1] = 0;
	result = NULL;
	while (TRUE)
	{
		tmp = result;
		if (read(fd, buf, 1) == 0)
		{
			if (!tmp)
				break ;
			ft_putstr_fd("  \b\b", fd);
			continue ;
		}
		result = ft_strjoin(result, (*buf == '\n' ? "" : buf));
		if (tmp)
			free(tmp);
		if (*buf == '\n')
			break ;
	}
	*line = result;
}
