/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:07:09 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/09 00:02:59 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string.h"

char	*ft_strrchr(const char *s, int c)
{
	char	to_find;
	char	*haystack;

	to_find = (char)(c);
	haystack = (char *)(s + ft_strlen(s));
	while (haystack >= (char *)s)
	{
		if (*haystack == to_find)
			return (haystack);
		haystack--;
	}
	return (NULL);
}
