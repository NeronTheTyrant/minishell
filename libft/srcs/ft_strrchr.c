/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:28:24 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 23:19:58 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: searches for the last occurrence of character c in string s
** return: address of last occurrecen of character c in string s if OK,
** NULL if KO
*/

char	*ft_strrchr(const char *s, int c)
{
	const char	*temp;

	temp = s;
	s += ft_strlen(s);
	while (temp < s && *s != (char)c)
		s--;
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}
