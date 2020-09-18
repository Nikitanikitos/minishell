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

void		print_double_array(char **array)
{
	while (*array)
		printf("%s\n", (*array)++);
}

void	print_arguments_list(t_list *commands)
{
	t_command	*command;

	printf("\n");
	while (commands)
	{
		printf("argument = %s|\n", (char*)commands->content);
		commands = commands->next;
	}
	printf("\n");
}

char	**convert_from_list_to_array(t_list *list)
{
	char		**array;
	const int	size_list = ft_lstsize(list);
	int 		i;

	if ((array = (char**)malloc(sizeof(char*) * (size_list + 1))) == NULL)
		return (NULL);
	i = 0;
	while (list)
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
	char	*cwd;


	if (first_time)
		write(STDOUT_FILENO, " \e[1:1H\e[2J", 12);
	first_time = 0;
	write(STDOUT_FILENO, "minishell~", 10);
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, 1);
	free(cwd);
	write(1, "~$ ", 3);
}

void	print_error(void)
{
	char	*error;

	error = strerror(errno);
	ft_putendl_fd(error, STDERR_FILENO);
}
