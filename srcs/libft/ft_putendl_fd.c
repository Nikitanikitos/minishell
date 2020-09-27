/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:54:19 by imicah            #+#    #+#             */
/*   Updated: 2020/05/11 13:19:07 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	const int	buff = ft_strlen(s);

	if (buff)
		write(fd, &(*s), buff);
	write(fd, "\n", 1);
}

void	ft_putstderr(char *s)
{
	write(2, "\e[31m\e[1m", 10);
	ft_putstr_fd(s, 2);
	write(2, "\e[0m\n", 6);
}