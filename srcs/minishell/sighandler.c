/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:42:11 by imicah            #+#    #+#             */
/*   Updated: 2020/09/16 15:42:12 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		type_prompt();
	}
}

void	eof_handler(void)
{
	ft_putendl_fd("exit", 1);
	exit(EXIT_SUCCESS);
}
