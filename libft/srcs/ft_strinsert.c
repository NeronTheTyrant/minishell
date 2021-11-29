/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:59:56 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/27 16:00:55 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Create a new string which is the result of the insertion of src into dst at 
** its pos'th index (what was on and after pos'th index in original dst will 
** be following the inserted string)
*/
char	*ft_strinsert(const char *dst, const char *src, size_t pos)
{
	char	*result;
	size_t	src_len;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (pos >= dst_len)
		pos = dst_len;
	src_len = ft_strlen(src);
	result = malloc(sizeof(char) * (dst_len + src_len + 1));
	if (!result)
		return (NULL);
	result[dst_len + src_len] = '\0';
	ft_memcpy(result, dst, pos);
	ft_memcpy(result + pos, src, src_len);
	ft_memcpy(result + pos + src_len, dst + pos, dst_len - pos);
	return (result);
}
