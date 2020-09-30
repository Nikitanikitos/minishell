/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <froxanne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:42:11 by imicah            #+#    #+#             */
/*   Updated: 2020/09/30 17:00:12 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	int		stat;
	int		pid;

	pid = waitpid(-1, &stat, WNOHANG);
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_status = 130;
		if (pid)
			type_prompt();
	}
}

void	eof_handler(void)
{
	ft_putendl_fd("\nexit", 1);
	exit(EXIT_SUCCESS);
}

void	quit(int num)
{
	int		stat;
	int		pid;

	(void)num;
	pid = waitpid(-1, &stat, WNOHANG);
	if (!pid)
		ft_putstr_fd("Quit: 3\n", 1);
	else
		ft_putstr_fd("\b\b  \b\b", 1);
}
