/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strextract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:03:23 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/27 16:03:51 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strextract(const char *dst, size_t start, size_t len)
{
	size_t	dst_len;
	size_t	tmp_len;
	char	*result;

	dst_len = ft_strlen(dst);
	if (dst_len <= start)
		return (ft_strdup(dst));
	tmp_len = ft_strlen(dst + start);
	if (tmp_len <= len)
		return (ft_strndup(dst, start));
	tmp_len = ft_strlen(dst + start + len);
	result = malloc(sizeof(char) * (dst_len - len + 1));
	if (result == NULL)
		return (NULL);
	result[dst_len - len] = '\0';
	ft_memcpy(result, dst, start);
	ft_memcpy(result + start, dst + start + len, tmp_len);
	return (result);
}
