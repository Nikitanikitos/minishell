/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 02:30:36 by imicah            #+#    #+#             */
/*   Updated: 2020/05/05 18:07:05 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char		ft_isspace(char c)
{
	return ((c == '\n' || c == '\t' || c == '\r' ||
			c == '\v' || c == '\f' || c == ' '));
}

int				ft_atoi(const char *nptr)
{
	int		result;
	char	pos_or_neg;

	result = 0;
	pos_or_neg = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*(nptr++) == '-')
			pos_or_neg = -1;
	while (*nptr >= '0' && *nptr <= '9')
		result = result * 10 + (*(nptr++) - '0');
	result *= pos_or_neg;
	return (result);
}
