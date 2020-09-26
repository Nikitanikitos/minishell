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
	return ((fds.std_write != 3 || fds.std_read != 4) && fds.fork == 1);
}

char	**convert_from_list_to_array(t_list *list, int size_array)
{
	char	**array;
	int		size_list;
	int		i;

	size_list = ft_lstsize(list);
	if (size_list > size_array)
		size_list = size_array;
	if ((array = (char**)malloc(sizeof(char*) * (size_list + 1))) == NULL)
		return (NULL);
	i = 0;
	while (list && size_array--)
	{
		array[i++] = ft_strdup(list->content);
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
	write(1, "$ ", 1);
}

void	print_error(char **arguments)
{
	char	*error;

	ft_putstr_fd("minishell: ", 2);
	while (*arguments)
	{
		ft_putstr_fd(*arguments++, 2);
		ft_putstr_fd(": ", 2);
	}
	error = strerror(errno);
	ft_putendl_fd(error, STDERR_FILENO);
}
