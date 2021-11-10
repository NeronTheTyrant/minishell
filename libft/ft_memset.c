/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:44:28 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/09 00:02:11 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*b_copy;
	unsigned char	c_copy;

	b_copy = (unsigned char *)b;
	c_copy = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		b_copy[i] = c_copy;
		i++;
	}
	return (b);
}
