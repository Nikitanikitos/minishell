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

int		cd(t_arguments *arguments, t_list *env_list)
{
	char		*cwd;

	if (*arguments->argv == NULL)
		chdir("/");
	else
	{
		ft_lower(*arguments->argv);
		chdir(*arguments->argv);
	}
	cwd = getcwd(NULL, 0);
	arguments->argv[0] = ft_strjoin("PWD=", cwd);
	free(cwd);
	export(arguments, env_list);
	return (errno);
}

int		ft_exit(t_arguments *arguments, t_list *env_list)
{
	int		exit_number;

	if (ft_str_double_len(arguments->argv) > 1)
	{
		errno = 7;
		return (errno);
	}
	else if (*arguments->argv && !ft_isdigit(*arguments->argv))
		print_error(arguments->argv, 0);
	if (!*arguments->argv)
		exit_number = 0;
	else
		exit_number = ft_atoi(*arguments->argv);
	ft_putendl_fd("exit", 1);
	ft_lstclear(env_list, &free_env);
	free_double_array(arguments->argv);
	exit(exit_number);
}
