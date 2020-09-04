/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:41:49 by imicah            #+#    #+#             */
/*   Updated: 2020/09/02 15:42:42 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

# define TRUE	1

void	type_prompt();

t_list	*get_commands_with_params_list(char *user_input);



typedef struct	s_command
{
	char		*command;
	char 		**parameters;
}				t_command;

void	print_command_and_parameters(t_command	*commands);
