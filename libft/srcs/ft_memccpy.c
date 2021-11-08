/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:54:54 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 21:56:23 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: copies up to n bytes from srcs to dst until character c is copied
** return: pointer to byte after c was copied in dest if OK, NULL if KO
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		ch;

	i = 0;
	d = dst;
	s = src;
	ch = c;
	while (i < n)
	{
		*d = *s;
		if (*d == ch)
			return (++d);
		d++;
		s++;
		i++;
	}
	return (0);
}
