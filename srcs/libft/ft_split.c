/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:53:54 by imicah            #+#    #+#             */
/*   Updated: 2020/05/03 15:32:24 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void		ft_split_free(char **dest)
{
	while (dest)
	{
		while (*dest)
			free(*dest++);
		free(dest++);
	}
}

static size_t	ft_count_chr(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i + 1);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	count;
	char	flag;

	count = 0;
	flag = 1;
	while (*s)
	{
		if (*s != c && flag)
		{
			count++;
			flag = 0;
		}
		else if (*s == c)
			flag = 1;
		s++;
	}
	return (count);
}

static char		**ft_write_words(const char *s, char **dest,
								char c, size_t count_word)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (*s && j < count_word)
	{
		k = 0;
		while (*s == c)
			s++;
		if (!(dest[j] = (char*)malloc(sizeof(char) * ft_count_chr(s, c))))
		{
			ft_split_free(dest);
			return (NULL);
		}
		while (*s != c && *s)
			dest[j][k++] = *(s++);
		dest[j++][k] = '\0';
	}
	dest[j] = 0;
	return (dest);
}

char			**ft_split(char const *s, char c)
{
	char	**result_s;
	size_t	count_word;

	count_word = ft_count_word(s, c);
	if (!(result_s = malloc(sizeof(char*) * (count_word + 1))))
		return (NULL);
	result_s = ft_write_words(s, result_s, c, count_word);
	return (result_s);
}
