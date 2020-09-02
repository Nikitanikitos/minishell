/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 23:34:14 by imicah            #+#    #+#             */
/*   Updated: 2020/05/05 17:30:11 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

int					ft_atoi(const char *nptr);
int					ft_strlen(const char *str);
int					ft_memcmp(const void *arr1, const void *arr2,
							size_t byte_sizes);

int					ft_strncmp(const char *arr1, const char *arr2,
							size_t byte_sizes);
size_t				ft_strlcpy(char *dst, const char *src, size_t byte_sizes);
size_t				ft_strlcat(char *dst, const char *src, size_t byte_sizes);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nbr, int fd);
void				ft_bzero(void *dest, size_t byte_sizes);
void				*ft_calloc(size_t num, size_t byte_sizes);
void 				*ft_realloc(char *src, int size);
void				*ft_memset(void *dest, int chr, size_t byte_sizes);
void				*ft_memchr(const void *arr, int c, size_t byte_sizes);
void				*ft_memcpy(void *dest, const void *src, size_t byte_sizes);
void				*ft_memmove(void *dest, const void *src, size_t byte_sizes);
void				*ft_memccpy(void *dest, const void *src, int c,
								size_t byte_sizes);


char				*ft_itoa(int n);
char				ft_isalnum(char c);
char				ft_isalpha(char c);
char				ft_isprint(char c);
char				ft_isascii(char c);
char				ft_isdigit(char c);
char				ft_tolower(char c);
char				ft_toupper(char c);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dest, char *src);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *str, char ch);
char				*ft_strrchr(const char *str, char ch);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(const char *s1, const char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				*ft_strnstr(const char *big, const char *little,
								size_t len);

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_lstsize(t_list *lst);

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));

void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));

#endif
