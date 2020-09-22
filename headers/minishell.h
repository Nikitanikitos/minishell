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
	int 		std_in;
	int 		std_out;
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
void			check_path(char **command, t_list *env_list);
void			eof_handler(void);
void			free_env(void *arg);
void			free_double_array(char **array);
void			move_list(t_list **list, int index);

void			sigint_handler(int signum);
void			type_prompt(void);
t_list			*parse_user_input(char *user_input, int *length, t_list *env_list);

void			parse_arguments_in_command(char ***arguments,t_list *env_list);
void			print_error(void);
void			print_arguments_list(t_list	*commands);
//void			print_export(t_list *env_list);

char			**convert_from_list_to_array(t_list *list, int size_array);
char			*get_env_value(char *key, t_list *env_list);
char			*parse_argument_with_double_quotes(char *parameters, t_list *env_list);
char			*parse_argument_with_single_quotes(char *parameters);
char			*parse_with_envp(char *parameters, t_list *env_list);

t_env			*env_init(char **key_value);

t_list			*get_env_list(char **envp);

int				get_fd(t_list	*arguments, t_fds *fds);
int				get_back_redirect(t_list *arguments, int index, t_fds *fds);
int				get_double_forward_redirect(t_list *arguments, int index, t_fds *fds);
int				get_forward_redirect(t_list *arguments, int index, t_fds *fds);
int				is_fork(t_fds fds);
int				get_next_quote(const char *str, char quote, int i);
int				str_get_index(const char *str, char *elements);
int				ft_get_index_array(char **arrays, char *array);

int				echo(t_arguments* arguments, t_list *env_list);
int				export(t_arguments *, t_list *env_list);
int				cd(t_arguments *command, t_list *env_list);
int				ft_exit(t_arguments*, t_list *env_list);
int				pwd(t_arguments*, t_list *env_list);
int				unset(t_arguments *command, t_list *env_list);
