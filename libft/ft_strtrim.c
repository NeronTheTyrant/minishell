/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:07:35 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/08 23:40:31 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string.h"
#include "ft_memory.h"

char	*ft_strtrim(char const *src, char const *set)
{
	size_t	len;
	size_t	i;

	if (!src)
		return (NULL);
	else if (!set)
		return (ft_strdup(src));
	i = 0;
	while (src[i] && ft_strchr(set, src[i]))
		i++;
	if (!src[i])
		return (ft_strdup(""));
	len = ft_strlen(src + i);
	while (src + i + len >= src && ft_strchr(set, src[i + len - 1]))
		len--;
	return (ft_strndup(src, len));
}
