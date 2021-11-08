/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:59:50 by mlebard           #+#    #+#             */
/*   Updated: 2020/12/03 20:52:17 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: appends up to dstsize - strlen(dst) - 1 character(s) from src to the
** end of dst. The string is null-terminated if dstsize > 0
** return: the length of the string that was attempted to be created. if
** dstsize < strlen(dst), the return value is dstsize + strlen(src)
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[j] && j < dstsize)
		j++;
	while (src[i] && j + i + 1 < dstsize)
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j + i < dstsize)
		dst[j + i] = '\0';
	while (src[i])
		i++;
	return (j + i);
}
