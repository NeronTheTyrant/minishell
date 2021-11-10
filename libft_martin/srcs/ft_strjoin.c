/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:47:30 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 23:17:42 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: creates a new malloc'd null-terminated string from the concatenation
** of strings s1 and s2
** return: new malloc'd string if OK, NULL if KO
*/

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*join;
	char	*temp;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(join) * (len + 1));
	if (join == NULL)
		return (NULL);
	temp = join;
	while (*s1)
	{
		*join = *s1;
		join++;
		s1++;
	}
	while (*s2)
	{
		*join = *s2;
		join++;
		s2++;
	}
	*join = '\0';
	return (temp);
}
