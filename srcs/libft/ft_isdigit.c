/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 02:49:43 by imicah            #+#    #+#             */
/*   Updated: 2020/05/01 13:46:35 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_digit(char c)
{
	return ('0' <= c && c <= '9');
}

int		ft_isdigit(char *s)
{
	while (*s)
	{
		if (!('0' <= *s && *s <= '9'))
			return (0);
		s++;
	}
	return (1);
}
