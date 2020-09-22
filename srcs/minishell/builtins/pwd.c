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

char	*get_destination_directory(char *directory)
{
	char	*new_path;
	char	*temp_path;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	temp_path = ft_strjoin("/", directory);
	new_path = ft_strjoin(cwd, temp_path);
	free(temp_path);
	free(cwd);
	return (new_path);
}

int		cd(t_arguments *command, t_list *env_list)
{
	char	*new_path;

	if (*(command->arguments)== NULL)
		new_path = ft_strdup("/");
	else if (*(command->arguments)[0] == '/' ||
		!ft_strncmp(*(command->arguments), "../", 3))
		new_path = ft_strdup(*(command->arguments));
	else
		new_path = get_destination_directory(*(command->arguments));
	chdir(new_path);
	free(new_path);
	return (errno);
}

int		ft_exit(t_arguments *command, t_list *env_list)
{
	ft_lstclear(env_list, &free_env);
	free_double_array(command->arguments);
	exit(0);
}
