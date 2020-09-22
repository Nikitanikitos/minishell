/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:40:22 by imicah            #+#    #+#             */
/*   Updated: 2020/09/17 11:33:29 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pwd(t_arguments *arguments, t_list *env_list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (errno);
}

int		cd(t_arguments *command, t_list *env_list)
{

	if (*command->arguments== NULL)
		chdir("/");
	else
	{
		ft_lower(*command->arguments);
		chdir(*command->arguments);
	}
	return (errno);
}

int		ft_exit(t_arguments *command, t_list *env_list)
{
	ft_lstclear(env_list, &free_env);
	free_double_array(command->arguments);
	exit(0);
}
