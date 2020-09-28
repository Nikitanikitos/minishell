/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:19:37 by imicah            #+#    #+#             */
/*   Updated: 2020/09/27 19:19:39 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_result(char *result, int index)
{
	if (result)
		result[index] = 0;
	else
		result = ft_strdup("\0");
	return (result);
}

int		add_in_result(char *result, char *temp, int i, int index)
{
	ft_strcpy(result + index, temp);
	free(temp);
	return (i);
}

int		add_in_argument(char **result, char *temp, int shift)
{
	int		argument_length;

	argument_length = ft_strlen(temp);
	*result = ft_realloc(*result, argument_length + 1);
	ft_strcpy(*result + shift, temp);
	free(temp);
	return (argument_length);
}

void	get_empty_pipe(char **temp_user_input, t_fds *fds)
{
	int		fd[2];

	(*temp_user_input)++;
	pipe(fd);
	close(fd[1]);
	fds->std_read = fd[0];
	dup2(fds->std_read, STDIN_FILENO);
	fds->fork = 0;
}

int		get_fd(char **temp_user_input, t_fds *fds, t_list *env_list, int *flag)
{
	if (**temp_user_input == '|')
	{
		fds->fork = 1;
		get_pipe_fd(temp_user_input, fds);
		return (1);
	}
	else if (**temp_user_input == '>')
	{
		fds->fork = 1;
		get_redirect_fd(temp_user_input, fds, env_list);
		*flag = 1;
	}
	else if (**temp_user_input == '<')
	{
		fds->back_redirect = 0;
		get_redirect_fd(temp_user_input, fds, env_list);
		dup2(fds->std_read, STDIN_FILENO);
	}
	return (0);
}
