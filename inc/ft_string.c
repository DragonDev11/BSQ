/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhmichi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:09:43 by mhmichi           #+#    #+#             */
/*   Updated: 2026/08/31 18:45:56 by mhmichi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

char	ft_is_printable(char c)
{
	return (c >= 32 && c <= 126);
}

int	ft_str_contains(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_count_words(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str && ft_str_contains(*str, charset) != -1)
		str++;
	while (*str)
	{
		if (ft_str_contains(*str, charset) == -1
			&& ft_str_contains(*(str + 1), charset) != -1 && *(str + 1))
			count++;
		if (ft_str_contains(*str, charset) == -1 && *(str + 1) == '\0')
		{
			count++;
			break ;
		}
		str++;
	}
	return (count);
}

char	*ft_strstr(char *str, char *to_find, int *word_length)
{
	int	i;

	i = 0;
	while (*str && ft_str_contains(*str, to_find) != -1)
		str++;
	while (*(str + i))
	{
		if (ft_str_contains(*(str + i), to_find) != -1)
			break ;
		i++;
	}
	*word_length = i;
	return (str + i);
}

char	*ft_strndup(char *src, unsigned int n)
{
	char			*dup;
	unsigned int	i;

	dup = (char *)malloc(n + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < n && src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**ft_split(char *str, char *charset)
{
	int		words;
	char	**split;
	int		i;
	int		word_length;

	words = ft_count_words(str, charset);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (i < words)
	{
		str = ft_strstr(str, charset, &word_length);
		if (word_length <= 0)
			continue ;
		str -= word_length;
		split[i] = ft_strndup(str, word_length);
		if (!split[i])
			return (NULL);
		str += word_length;
		i++;
	}
	split[i] = NULL;
	return (split);
}
