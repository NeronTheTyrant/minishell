/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:08:07 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/28 05:35:03 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: duplicated string s using malloc
** return: new duplicated string if OK, NULL if KO
*/

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*temp;

	s2 = malloc(sizeof(*s2) * (ft_strlen(s1) + 1));
	if (s2 == NULL)
		return (NULL);
	temp = s2;
	while (*s1)
	{
		*s2 = *s1;
		s1++;
		s2++;
	}
	*s2 = '\0';
	return (temp);
}
