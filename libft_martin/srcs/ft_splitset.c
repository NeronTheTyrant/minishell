/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:05:14 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/28 01:04:25 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countwords(char const *s, char *set)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s && ft_isin(*s, set) != -1)
			s++;
		if (*s && ft_isin(*s, set) == -1)
			i++;
		while (*s && ft_isin(*s, set) == -1)
			s++;
	}
	return (i);
}

static size_t	getwordlen(char const *s, char *set)
{
	size_t	i;

	i = 0;
	while (*s && ft_isin(*s, set) == -1)
	{
		i++;
		s++;
	}
	return (i);
}

static char	**error_free(char **args)
{
	ft_freeargs(args);
	return (NULL);
}

static char	*isolate_word(char const *s, size_t len)
{
	char	*new;

	new = malloc(sizeof(*new) * len + 1);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, s, len);
	new[len] = '\0';
	return (new);
}

/*
** usage: separates string s with stric *set, then mallocs the resulting strings
** in a string array new. If mallocs fails, frees everything previously
** malloc'd
**  return: null-terminated string array strs if OK, NULL if KO
*/

char	**ft_splitset(char const *s, char *set)
{
	char	**new;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s)
		return (NULL);
	j = countwords(s, set);
	i = 0;
	new = malloc(sizeof(*new) * (j + 1));
	if (new == NULL)
		return (NULL);
	while (i < j)
	{
		while (*s && ft_isin(*s, set) != -1)
			s++;
		len = getwordlen(s, set);
		new[i] = isolate_word(s, len);
		if (new[i] == NULL)
			return (error_free(new));
		s += len;
		i++;
	}
	new[i] = NULL;
	return (new);
}
