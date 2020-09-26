/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <froxanne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 16:14:56 by froxanne          #+#    #+#             */
/*   Updated: 2020/09/26 16:38:29 by froxanne         ###   ########.fr       */
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
		if (((readed = read(fd, buf, 1)) == 0) && i == 0)
			break ;
		if (readed == 0)
			continue ;
		if (*buf == '\n')
			break ;
		tmp = result;
		result = ft_strjoin(result, buf);
		if (tmp)
			free(tmp);
		i++;
	}
	*line = result;
}