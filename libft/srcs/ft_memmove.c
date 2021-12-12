/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:58:56 by mlebard           #+#    #+#             */
/*   Updated: 2020/12/03 19:59:20 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: copies len bytes from array src into array dst. handles overlaps
** return: start of copied array dst
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (len == 0 || dst == src)
		return (dst);
	if ((unsigned long int)dst < (unsigned long int)src)
		return (ft_memcpy(dst, src, len));
	else
	{
		i = len;
		d = dst;
		s = src;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	return (dst);
}
