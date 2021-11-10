/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:42:38 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/10 21:05:10 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	*ft_memmove_from_end(void *dst, const void *src, size_t len)
{	
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	dst_ptr = (unsigned char *)(dst + len);
	src_ptr = (unsigned char *)(src + len);
	while (len)
	{
		len--;
		dst_ptr--;
		src_ptr--;
		*dst_ptr = *src_ptr;
	}
	return (dst);
}

static void	*ft_memmove_from_begin(void *dst, const void *src, size_t len)
{	
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	dst_ptr = (unsigned char *)(dst);
	src_ptr = (unsigned char *)(src);
	while (len)
	{
		len--;
		*dst_ptr = *src_ptr;
		dst_ptr++;
		src_ptr++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src < dst)
		return (ft_memmove_from_end(dst, src, len));
	else
		return (ft_memmove_from_begin(dst, src, len));
}
