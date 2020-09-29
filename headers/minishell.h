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

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/dir.h>
# include "libft.h"

# define NUMBER_BUILDIN_CMD	7
# define TRUE				1
# define FALSE				0

int				g_status;

typedef struct	s_fds
{
	int			std_write;
	int			std_read;
	int			fork;
	int			back_redirect;
}				t_fds;

typedef struct	s_arguments
{
	char		**argv;
	t_fds		fds;
}				t_arguments;

typedef struct	s_builtin
{
	char		*func_name;
	int			(*func)(t_arguments*, t_list*);
}				t_builtin;

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

void			add_env(t_list *env_list, t_env *env);
void			arguments_init(t_arguments *arguments);
void			check_path(char **command, t_list *env_list);
void			eof_handler(void);
void			get_empty_pipe(char **temp_user_input, t_fds *fds);
void			get_pipe_fd(char **arguments, t_fds *fds);
void			get_redirect_fd(char **arguments, t_fds *fds, t_list *env_list);
void			ft_put_redirect_error(t_fds fds);
void			free_env(void *arg);
void			free_double_array(char **array);
void			read_line(int fd, char **line);
void			print_error(char **arguments, int error_number);
void			type_prompt(void);
void			quit(int num);
void			sigint_handler(int signum);
void			ft_put_error_pipe();

char			*check_result(char *result, int index);
char			**convert_from_list_to_array(t_list *list);
char			*get_env_value(char *key, t_list *env_list);
char			*parse_argument(char **user_input, t_list *env_list);
char			*parse_with_envp(char **argument, t_list *env_list);
char			**parse_user_input(char **usr_input, t_list *env_list,
																	t_fds *fds);

t_env			*env_init(char **key_value);
t_list			*get_env_list(char **envp);

int 			check_incorrect_pipe(char *s);
int				add_in_argument(char **result, char *temp, int shift);
int				add_in_result(char *result, char *temp, int i, int index);
int				echo(t_arguments *arguments, t_list *env_list);
int				get_fd(char **temp_user_input, t_fds *fds, t_list *env_list,
																	int *flag);

int				cd(t_arguments *arguments, t_list *env_list);
int				env(t_arguments *arguments, t_list *env_list);
int				export(t_arguments *arguments, t_list *env_list);
int				is_fork(t_fds fds);
int				ft_exit(t_arguments *arguments, t_list *env_list);
int				pwd(t_arguments *arguments, t_list *env_list);
int				unset(t_arguments *arguments, t_list *env_list);

#endif
