/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:37:05 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/07 23:31:06 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	letter;

	str = (unsigned char *)(s);
	letter = (unsigned char)(c);
	i = 0;
	while (i < n)
	{
		if (*(str + i) == letter)
			return (str + i);
		i++;
	}
	return (NULL);
}
