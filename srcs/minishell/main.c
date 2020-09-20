/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 15:41:20 by imicah            #+#    #+#             */
/*   Updated: 2020/09/17 11:31:25 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_buildin_command(t_command command, t_list *env_list)
{
	int				index;
	const t_builtin	builtins[] = {
			{"echo", &echo},
			{"cd", &cd},
			{"pwd", &pwd},
			{"export", &export},
			{"unset", &unset},
			{"env", NULL},
			{"exit", &ft_exit},
	};

	index = 0;
	while (index < NUMBER_BUILDIN_CMD)
	{
		if (!ft_strcmp(builtins[index].func_name, *(command.arguments)))
		{
			command.arguments++;
			if (builtins[index].func(&command, env_list))
				print_error();
			return (TRUE);
		}
		index++;
	}
	return (FALSE);
}

void	start_process(t_command *command, t_list *env_list)
{
	pid_t		pid;
	char		**env;
	int			status;

	errno = 0;
	if (execute_buildin_command(*command, env_list))
		;
	else if ((pid = fork()))
		waitpid(-1, &status, 0);
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		check_path(command->arguments, env_list);
		if ((status = execve(*(command->arguments), command->arguments, env)))
		{
			print_error();
			exit(status);
		}
	}
}

//void	get_fd(t_command *command)
//{
//	int		index;
//
//	index = 0;
//	while (command->arguments[index])
//	{
//		if (ft_strnstr(command->arguments[index], ">", 1))
//			return (get_forward_redirect(command, index));
//		else if (ft_strnstr(command->arguments[index], ">>", 2))
//			get_double_forward_redirect(command, index);
//		else if (ft_strnstr(command->arguments[index], "<", 1))
//			get_back_redirect(command, index);
//		else if (ft_strnstr(command->arguments[index], "|", 1))
//			get_pipe(command, index);
//		index++;
//	}
//}

t_list	*minishell(char *user_input, t_list *env_list)
{
	t_command	*command;
	int 		length;

	while (*user_input)
	{
		length = 0;
		if (*user_input == ';')
			user_input++;
		else
		{
			command = parse_user_input(user_input, &length, env_list);
			command->fd[0] = 1;
			command->fd[1] = 0;
//			while (command->arguments)
//			{
//				get_fd(command);
				parse_arguments_in_command(command->arguments, env_list);
				start_process(command, env_list);
//				(command->arguments)++;
//				while()
//			}
		}
		user_input += length;
	}
	return (NULL);
}

int		main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_list		*env_list;

	signal(SIGINT, sigint_handler); // TODO добить сигналы
	if ((env_list = get_env_list(envp)) == NULL)
		exit(1);
	while (TRUE)
	{
		type_prompt();
		get_next_line(0, &user_input);
		if (!*user_input)
			eof_handler();
		else if (*user_input == '\n')
			*user_input = 0;
		minishell(user_input, env_list);
		free(user_input);
	}
	return (0);
}

//#include <sys/types.h>
//#include <unistd.h>
//#include <stdio.h>
//int main()
//{
//	int fd[2];
//	size_t size;
//	char string[] = "Hello, world!";
//	char resstring[14];
//	/* Попытаемся создать pipe */
//	if(pipe(fd) < 0){
//		/* Если создать pipe не удалось, печатаем об этом сообщение
//		и прекращаем работу */
//		printf("Can\'t create pipe\n");
//		exit(-1);
//	}
//	/* Пробуем записать в pipe 14 байт из нашего массива, т.е. всю
//	строку "Hello, world!" вместе с признаком конца строки */
//	size = write(fd[1], string, 14);
//	if(size != 14)
//	{
//		/* Если записалось меньшее количество байт, сообщаем об
//		ошибке */
//		printf("Can\'t write all string\n");
//		exit(-1);
//	}
//	/* Пробуем прочитать из pip'а 14 байт в другой массив, т.е. всю
//	записанную строку */
//	size = read(fd[0], resstring, 14);
//	if(size < 0)
//	{
//		/* Если прочитать не смогли, сообщаем об ошибке */
//		printf("Can\'t read string\n");
//		exit(-1);
//	}
//	/* Печатаем прочитанную строку */
//	printf("%s\n",resstring);
//	/* Закрываем входной поток*/
//	if(close(fd[0]) < 0)
//	{
//		printf("Can\'t close input stream\n");
//	}
//	/* Закрываем выходной поток*/
//	if(close(fd[1]) < 0)
//	{
//		printf("Can\'t close output stream\n");
//	}
//	return 0;
//}
//
//#include <sys/types.h>
//#include <unistd.h>
//#include <stdio.h>
//int main(){
//	int fd[2], result;
//	size_t size;
//	char resstring[14];
//	/* Попытаемся создать pipe */
//	if(pipe(fd) < 0){
//		/* Если создать pipe не удалось, печатаем об этом сообщение
//		и прекращаем работу */
//		printf("Can\'t create pipe\n");
//		exit(-1);
//	}
//	/* Порождаем новый процесс */
//	result = fork();
//	if(result)
//	{
//		/* Если создать процесс не удалось, сообщаем об этом и
//		завершаем работу */
//		printf("Can\'t fork child\n");
//		exit(-1);
//	}
//	else if (result > 0)
//	{
//		/* Мы находимся в родительском процессе, который будет
//		передавать информацию процессу-ребенку. В этом процессе
//		выходной поток данных нам не понадобится, поэтому
//		закрываем его.*/
//		close(fd[0]);
//		/* Пробуем записать в pipe 14 байт, т.е. всю строку
//		"Hello, world!" вместе с признаком конца строки */
//		size = write(fd[1], "Hello, world!", 14);
//		if(size != 14)
//		{
//			/* Если записалось меньшее количество байт, сообщаем
//			об ошибке и завершаем работу */
//			printf("Can\'t write all string\n");
//			exit(-1);
//		}
//		/* Закрываем входной поток данных, на этом
//		родитель прекращает работу */
//		close(fd[1]);
//		printf("Parent exit\n");
//	}
//	else
//	{
//		/* Мы находимся в порожденном процессе, который будет
//		получать информацию от процесса-родителя. Он унаследовал
//		от родителя таблицу открытых файлов и, зная файловые
//		дескрипторы, соответствующие pip, иможет его использовать.
//		В этом процессе входной поток данных нам не
//		ипонадобится, поэтому закрываем его.*/
//		close(fd[1]);
//		/* Пробуем прочитать из pip'а 14 байт в массив, т.е. всю
//		записанную строку */
//		size = read(fd[0], resstring, 14);
//		if(size < 0)
//		{
//
//			/* Если прочитать не смогли, сообщаем об ошибке и
//			завершаем работу */
//
//			printf("Can\'t read string\n");
//			exit(-1);
//		}
//		/* Печатаем прочитанную строку */
//		printf("%s\n",resstring);
//		/* Закрываем входной поток и завершаем работу */
//		close(fd[0]);
//	}
//	return 0;
//}