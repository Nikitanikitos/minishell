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

#include <stdio.h> // TODO удалить!

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/dir.h>
#include "libft.h"

# define NUMBER_BUILDIN_CMD	7
# define TRUE				1
# define FALSE				0

typedef struct	s_arguments
{
	char		*command;
	char 		**parameters;
}				t_arguments;

typedef struct	s_builtin
{
	char		*command;
	int 		(*func)(void*, t_list*);
}				t_builtin;

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

t_arguments		*arguments_init(char **command);
t_env			*env_init(char **key_value);

t_list			*get_commands_list(char *user_input);
t_list			*get_env_list(char **envp);

void			change_or_add_value_env(char **key_value, t_list **env_list);

void			type_prompt();
void			print_error(void);
void			print_arguments_list(t_list	*commands);

void			print_export(t_list *env_list);

void			free_list(t_list *list);
void			free_double_array(char **array);

int				echo(void* arguments, t_list *env_list);
int				pwd(void*, t_list *env_list);
int				cd(void *arguments, t_list *env_list);
int				export(void *x, t_list *env_list);
int				ft_exit(void*, t_list *env_list);

int				execute_buildin_command(t_arguments arguments, t_list *env_list);
