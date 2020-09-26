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
		write(STDOUT_FILENO, " \e[1:1H\e[2J", 12);
	first_time = 0;
	write(STDOUT_FILENO, "minishell:~", 11);
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, 1);
	free(cwd);
	write(1, "$ ", 2);
}

void	print_error(char **arguments, int error_number)
{
	char	*error;

	ft_putstr_fd("minishell: ", 2);
	while (arguments && *arguments)
	{
		ft_putstr_fd(*arguments++, 2);
		ft_putstr_fd(": ", 2);
	}
	error = strerror(errno);
	if (!error_number)
		ft_putendl_fd(error, STDERR_FILENO);
	else
		ft_putendl_fd("command not found", STDERR_FILENO);
}
