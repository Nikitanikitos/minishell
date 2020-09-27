# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: froxanne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/30 19:02:03 by imicah            #+#    #+#              #
#    Updated: 2020/09/17 10:23:25 by froxanne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRCS		= $(shell find . -type f -name '*.c' -not -name 'ft_lst*.c')
SRCS_BONUS	= $(shell find . -type f -name 'ft_lst*.c')
SRCS_SO		= $(shell find . -type f -name 'ft_*.c')

OBJS		= $(SRCS:%.c=%.o)
OBJS_BONUS	= $(SRCS_BONUS:%.c=%.o)

INCLUDES    = -I../../headers
GCC			= gcc -Wall -Wextra -Werror

.PHONY: clean fclean all so bonus

#######################################################

all: $(NAME) bonus

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o : %.c
	$(GCC) -g $(INCLUDES) -o $@ -c $<

#######################################################

bonus: $(OBJS_BONUS)
	ar -rc $(NAME) $(OBJS_BONUS)
	ranlib $(NAME)

#######################################################

so: $(NAME_SO)

$(NAME_SO): $(OBJS_SO)
	gcc -shared -o $(NAME_SO) $(OBJS_SO)

#######################################################

main:
	gcc -Wall -Wextra -Werror main.c -L. -lft -lbsd libft.a -o main

#######################################################

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	rm -f $(OBJS_SO)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_SO)

re: fclean all
