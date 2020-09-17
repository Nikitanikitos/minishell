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

int		cd(t_arguments *arguments, t_list *env_list)
{
	char				*new_path;

	if (arguments->parameters[1] == NULL)
		new_path = ft_strdup("/");
	else if (arguments->parameters[1][0] == '/' ||
		!ft_strncmp(arguments->parameters[1], "../", 3))
		new_path = ft_strdup(arguments->parameters[1]);
	else
		new_path = get_destination_directory(arguments->parameters[1]);
	chdir(new_path);
	free(new_path);
	return (errno);
}

int		ft_exit(t_arguments *arguments, t_list *env_list)
{
	ft_lstclear(env_list, &free_env);
	free_double_array(arguments->parameters); // free only 1 arg, need free all list;
	exit(0);
}
