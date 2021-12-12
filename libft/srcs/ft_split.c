/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 02:26:51 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/28 05:33:05 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		while (*s && *s != c)
			s++;
		if (*(s - 1) != c)
			i++;
	}
	return (i);
}

static char	*ft_strdup_charset(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	while (s[j] && s[j] != c)
		j++;
	str = malloc(sizeof(str) * (j + 1));
	if (str == NULL)
		return (NULL);
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	*ft_free_array(char **strs)
{
	int	k;

	k = 0;
	while (strs[k])
	{
		free(strs[k]);
		k++;
	}
	free(strs);
	return (NULL);
}

/*
** usage: separates string s with char c, then mallocs the resulting strings
** in a string array strs. If mallocs fails, frees everything previously
** malloc'd
**
** return: null-terminated string array strs if OK, NULL if KO
*/

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_countwords(s, c);
	strs = malloc(sizeof(s) * (j + 1));
	if (strs == NULL)
		return (NULL);
	while (i < j)
	{
		while (*s == c)
			s++;
		strs[i] = ft_strdup_charset(s, c);
		if (strs[i] == NULL)
			return (ft_free_array(strs));
		i++;
		while (*s && *s != c)
			s++;
	}
	strs[i] = NULL;
	return (strs);
}
