/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:54:45 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/07 23:31:51 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	to_find;

	to_find = (char)(c);
	while (*s && *s != to_find)
		s++;
	if (*s == to_find)
		return ((char *)(s));
	else
		return (NULL);
}
