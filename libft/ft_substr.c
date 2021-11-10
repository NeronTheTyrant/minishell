/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:10:48 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/09 00:05:21 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_memory.h"

char	*ft_substr(char const *src, size_t start, size_t len)
{
	char	*dst;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (start > src_len)
		start = src_len;
	src_len = ft_strlen(src + start);
	if (len > src_len)
		len = src_len;
	dst = ft_strndup(src + start, len);
	return (dst);
}
