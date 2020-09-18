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

typedef struct	s_arguments
{
	char		**arguments;
	int 		*fd;
}				t_command;

typedef struct	s_builtin
{
	char		*command;
	int 		(*func)(t_command*, t_list*);
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
void			sigint_handler(int signum);
void			type_prompt(void);
void			print_error(void);
void			print_arguments_list(t_list	*commands);
void			print_export(t_list *env_list);

char			**convert_from_list_to_array(t_list *list);
char			*get_env_value(char *key, t_list *env_list);
char			*parse_argument_with_double_quotes(char *parameters, t_list *env_list);
char			*parse_argument_with_single_quotes(char *parameters);
char			*parse_with_envp(char *parameters, t_list *env_list);

t_env			*env_init(char **key_value);

t_list			*get_env_list(char **envp);

t_command		*arguments_init(char **command);
t_command		*parse_user_input(char *user_input, int *length, t_list *env_list);

int				get_next_quote(const char *str, char quote, int i);
int				str_get_index(const char *str, char *elements);

int				echo(t_command* command, t_list *env_list);
int				export(t_command *, t_list *env_list);
int				cd(t_command *command, t_list *env_list);
int				ft_exit(t_command*, t_list *env_list);
int				pwd(t_command*, t_list *env_list);
int				unset(t_command *command, t_list *env_list);
