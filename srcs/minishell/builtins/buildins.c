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

int		echo(t_arguments *arguments, t_list *env_list)
{
	int		flag;

	(void)env_list;
	flag = 1;
	if (*arguments->argv && !ft_strcmp(*(arguments->argv), "-n"))
	{
		flag = 0;
		arguments->argv++;
	}
	while (*(arguments->argv))
	{
		ft_putstr_fd(*(arguments->argv)++, 1);
		if (*(arguments->argv))
			write(1, " ", 1);
	}
	write(1, "\n", (size_t)flag);
	return (errno);
}

int		pwd(t_arguments *arguments, t_list *env_list)
{
	char	*cwd;

	(void)arguments;
	(void)env_list;
	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (errno);
}

void	export_home_env(char *key, t_list *env_list)
{
	t_arguments	argument;
	char		*arg[2];
	char		*cwd;

	cwd = getcwd(NULL, 0);
	arg[0] = ft_strjoin(key, cwd);
	arg[1] = NULL;
	argument.argv = arg;
	export(&argument, env_list);
	free(cwd);
	free(arg[0]);
}

int		cd(t_arguments *arguments, t_list *env_list)
{
	char	*home;

	export_home_env("OLDPWD=", env_list);
	if (*arguments->argv == NULL)
	{
		home = get_env_value("HOME", env_list);
		if (*home)
			chdir(home);
		else
		{
			ft_putstderr("minishell: cd: HOME not set");
			return (errno);
		}
	}
	else
	{
		ft_lower(*arguments->argv);
		chdir(*arguments->argv);
	}
	export_home_env("PWD=", env_list);
	return (errno);
}

int		ft_exit(t_arguments *arguments, t_list *env_list)
{
	const int	arg_number = ft_str_double_len(arguments->argv);

	(void)env_list;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!*arguments->argv || arg_number == 0)
		exit(0);
	else if (arg_number == 1)
	{
		if (is_correct_number(*arguments->argv))
			exit(ft_atoi(*arguments->argv));
		else
		{
			ft_putstr_fd("\e[1m\e[31mminishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(*arguments->argv, STDERR_FILENO);
			ft_putendl_fd(": a numeric is required\e[0m", STDERR_FILENO);
			exit(255);
		}
	}
	else
		ft_putstderr("minishell: exit: argument list too long");
	if (!is_correct_number(*arguments->argv))
		exit(255);
	return (0);
}
