#include "minishell.h"

int 	get_pipe(t_fds *fds, int index)
{
	int 	fd[2];

	pipe(fd);
	fds->std_in = fd[0];
	fds->std_out = fd[1];
	return (index);
}

int		get_fd(t_list	*arguments, t_fds *fds)
{
	int		index;
	char 	*argument;

	index = 0;
	while (arguments)
	{
		argument = (char*)arguments->content;
		if (!ft_strcmp(argument, ">"))
			return (get_forward_redirect(arguments, index, fds));
		else if (!ft_strcmp(argument, ">>"))
			return (get_double_forward_redirect(arguments, index, fds));
		else if (!ft_strcmp(argument, "<"))
			return (get_back_redirect(arguments, index, fds) + 2);
		else if (!ft_strcmp(argument, "|"))
			return (get_pipe(fds, index));
		arguments = arguments->next;
		index++;
	}
	fds->std_in = 3;
	fds->std_out = 4;
	return (index);
}
