/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:53:31 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/11 15:46:32 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memory.h"

static size_t	ft_count_words(char const *s, char sep)
{
	size_t	i;
	size_t	words_count;

	i = 0;
	words_count = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i])
			words_count++;
		while (s[i] && s[i] != sep)
			i++;
	}
	return (words_count);
}

static size_t	ft_count_letters(char const *s, char sep)
{
	size_t	count;

	count = 0;
	while (s[count] && s[count] != sep)
		count++;
	return (count);
}

static char	*ft_alloc_word(char const *s, char c, size_t word)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	j = 0;
	while (j < word)
	{
		while (s[i] == c)
			i++;
		j++;
		while (s[i] && s[i] != c)
			i++;
	}
	j = 0;
	while (s[i] == c)
		i++;
	result = (char *)malloc(ft_count_letters(s + i, c) + 1);
	if (!result)
		return (NULL);
	while (s[i] && s[i] != c)
		result[j++] = s[i++];
	result[j] = '\0';
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	words_count;
	size_t	i;

	words_count = ft_count_words(s, c);
	result = (char **)malloc(sizeof(*result) * (words_count + 1));
	if (!result)
		return (NULL);
	result[words_count] = NULL;
	i = 0;
	while (i < words_count)
	{
		result[i] = ft_alloc_word(s, c, i);
		if (!result[i])
			return (ft_free_tab((void **)result));
		i++;
	}
	return (result);
}
