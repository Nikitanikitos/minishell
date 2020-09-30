/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 19:40:10 by imicah            #+#    #+#             */
/*   Updated: 2020/09/04 19:40:12 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_fork(t_fds fds)
{
	return ((fds.std_write != 3 || fds.std_read != 4)
			&& fds.fork == 1 && fds.back_redirect == 0);
}

char	**convert_from_list_to_array(t_list *list)
{
	char	*temp;
	char	**array;
	t_env	*env;
	int		size_list;
	int		i;

	size_list = ft_lstsize(list);
	i = 0;
	if ((array = (char**)malloc(sizeof(char*) * (size_list + 1))) == NULL)
		return (NULL);
	while (list)
	{
		env = list->content;
		if (env->value && *env->value)
		{
			temp = ft_strjoin(env->key, "=");
			array[i++] = ft_strjoin(temp, env->value);
			free(temp);
		}
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

void	type_prompt(void)
{
	static int	first_time = 1;
	char		*cwd;

	if (first_time)
		ft_putstr_fd(" \e[1:1H\e[2J", STDOUT_FILENO);
	first_time = 0;
	ft_putstr_fd("\e[1mminishell:~", STDOUT_FILENO);
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("$\e[0m ", STDOUT_FILENO);
	free(cwd);
}

void	print_error(char **arguments)
{
	char	*error;

	ft_putstr_fd("\e[31m\e[1mminishell: ", STDERR_FILENO);
	while (arguments && *arguments)
	{
		ft_putstr_fd(*arguments++, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	error = strerror(errno);
	if (errno)
		ft_putendl_fd(error, STDERR_FILENO);
	else
		ft_putendl_fd("command not found", STDERR_FILENO);
	ft_putstr_fd("\e[0m", STDERR_FILENO);
	g_status = 1;
}

void	ft_put_redirect_error(char **arguments, t_fds fds)
{
	g_status = 258;
	if (errno)
	{
		print_error(arguments);
		g_status = 1;
	}
	else if (fds.std_write == -1)
		ft_putstderr("minishell: syntax error near unexpected token '>'");
	else if (fds.std_read == -1)
		ft_putstderr("minishell: No such file or directory");
	else if (fds.std_write == -2)
		ft_putstderr("minishell: syntax error near unexpected token '>>'");
	else if (fds.std_read == -2)
		ft_putstderr("minishell: syntax error near unexpected token '<'");
}
