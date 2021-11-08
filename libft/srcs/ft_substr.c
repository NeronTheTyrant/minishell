/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:48:56 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 23:21:05 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: creates a null-terminated copy of string s that starts at index start
** and has a maximum length of len.
** return: newly-created string if OK, NULL if KO
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start < ft_strlen(s))
		while (s[start + i] && i < len)
			i++;
	str = malloc(sizeof(*str) * (i + 1));
	if (str == NULL)
		return (NULL);
	while (j < i)
	{
		str[j] = s[start + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
