/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <froxanne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:20:40 by froxanne          #+#    #+#             */
/*   Updated: 2020/09/20 15:34:37 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pipe_fd(char **arguments, t_fds *fds)
{
	int		fd[2];

	pipe(fd);
	(*arguments)++;
	fds->std_write = fd[1];
	fds->std_read = fd[0];
}

int		get_forward_redirect(char **arguments, t_list *env_list)
{
	char			*temp_arguments;
	char			*file_name;
	static int		fd;

	if (fd != 0)
		close(fd);
	temp_arguments = *arguments;
	temp_arguments++;
	while (ft_isspace(*temp_arguments))
		temp_arguments++;
	file_name = parse_argument(&temp_arguments, env_list);
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(file_name);
	*arguments = temp_arguments;
	return (fd);
}

int		get_double_forward_redirect(char **arguments, t_list *env_list)
{
	char			*temp_arguments;
	char			*file_name;
	static int		fd;

	if (fd != 0)
		close(fd);
	temp_arguments = *arguments;
	temp_arguments += 2;
	while (ft_isspace(*temp_arguments))
		temp_arguments++;
	file_name = parse_argument(&temp_arguments, env_list);
	fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	free(file_name);
	*arguments = temp_arguments;
	return (fd);
}

int		get_back_redirect(char **arguments, t_list *env_list)
{
	char			*temp_arguments;
	char			*file_name;
	static int		fd;

	if (fd != 0)
		close(fd);
	temp_arguments = *arguments;
	temp_arguments++;
	while (ft_isspace(*temp_arguments))
		temp_arguments++;
	file_name = parse_argument(&temp_arguments, env_list);
	fd = open(file_name, O_CREAT | O_RDONLY, 0644);
	free(file_name);
	*arguments = temp_arguments;
	return (fd);
}

void	get_redirect_fd(char **arguments, t_fds *fds, t_list *env_list)
{
	char	*temp_arguments;

	temp_arguments = *arguments;
	fds->std_read = 0;
	fds->std_write = 1;
	while (*temp_arguments)
	{
		while (ft_isspace(*temp_arguments))
			temp_arguments++;
		if (!ft_strncmp(temp_arguments, ">>", 2))
			fds->std_write = get_double_forward_redirect(&temp_arguments, env_list);
		else if (!ft_strncmp(temp_arguments, ">", 1))
			fds->std_write = get_forward_redirect(&temp_arguments, env_list);
		else if (!ft_strncmp(temp_arguments, "<", 1))
			fds->std_read = get_back_redirect(&temp_arguments, env_list);
		else
			break;
	}
	*arguments = temp_arguments;
}
