/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:41:49 by imicah            #+#    #+#             */
/*   Updated: 2020/09/17 10:21:22 by froxanne         ###   ########.fr       */
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

typedef struct	s_fds
{
	int 		std_write;
	int 		std_read;
}				t_fds;

typedef struct	s_arguments
{
	char		**arguments;
	t_fds		fds;
}				t_arguments;

typedef struct	s_builtin
{
	char		*func_name;
	int 		(*func)(t_arguments*, t_list*);
}				t_builtin;

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

void			add_env(t_list *env_list, t_env *env);
void			eof_handler(void);
void			free_env(void *arg);
void			free_double_array(char **array);

void			sigint_handler(int signum);
void			type_prompt(void);
char			**parse_user_input(char **user_input, t_list *env_list, t_fds *fds);
void			get_pipe_fd(char **arguments, t_fds *fds);
void			get_redirect_fd(char **arguments, t_fds *fds, t_list *env_list);

void			print_error(char **arguments);

char			*parse_argument(char **user_input, t_list *env_list);
char			*get_env_value(char *key, t_list *env_list);
char			*parse_with_envp(char **argument, t_list *env_list);

t_env			*env_init(char **key_value);
t_list			*get_env_list(char **envp);

int				check_path(char **command, t_list *env_list);
int				is_fork(t_fds fds);
int				echo(t_arguments* arguments, t_list *env_list);
int				env(t_arguments *arguments, t_list *env_list);
int				export(t_arguments *, t_list *env_list);
int				cd(t_arguments *command, t_list *env_list);
int				ft_exit(t_arguments*, t_list *env_list);
int				pwd(t_arguments*, t_list *env_list);
int				unset(t_arguments *arguments, t_list *env_list);
