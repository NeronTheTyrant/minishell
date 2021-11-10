/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:34:22 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/07 23:30:17 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;
	unsigned char	c_tmp;

	dst_tmp = (unsigned char *)dst;
	src_tmp = (unsigned char *)src;
	c_tmp = (unsigned char)(c);
	i = 0;
	while (i < n)
	{
		dst_tmp[i] = src_tmp[i];
		if (dst_tmp[i] == c_tmp)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
