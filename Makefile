# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/14 19:06:46 by imicah            #+#    #+#              #
#    Updated: 2020/09/14 19:06:48 by imicah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME    = minishell

SRCS    = $(shell find srcs/minishell -type f -name '*.c' )
OBJS    = $(SRCS:%.c=%.o)
LIBFT   = srcs/libft/libft.a

HEADERS = -Iheaders/

# FLAGS   = -Wall -Wextra -Werror
FLAGS   =

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	gcc ${FLAGS} ${HEADERS} ${OBJS} $(LIBFT) -o ${NAME}

$(LIBFT):
	$(MAKE) -C srcs/libft

%.o: %.c
	gcc ${FLAGS} ${HEADERS} -o $@ -c $<

clean:
	rm -f $(OBJS)
	rm -f srcs/libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all
