/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <froxanne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 16:14:56 by froxanne          #+#    #+#             */
/*   Updated: 2020/09/29 12:02:12 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_line(int fd, char **line)
{
	char	buf[2];
	char	*tmp;
	char	*result;
	int		readed;
	int		i;

	i = 0;
	buf[1] = 0;
	result = NULL;
	while (1)
	{
		tmp = result;
		if (((readed = read(fd, buf, 1)) == 0) && i == 0)
			break ;
		if (readed == 0)
		{
			ft_putstr_fd("  \b\b", fd);
			continue ;
		}
		result = ft_strjoin(result, (*buf == '\n' ? "" : buf));
		if (tmp)
			free(tmp);
		if (*buf == '\n')
			break ;
		i++;
	}
	*line = result;
}
