/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:38:51 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/07 23:30:44 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;

	if (n == 0)
		return (0);
	s1_tmp = (unsigned char *)(s1);
	s2_tmp = (unsigned char *)(s2);
	i = 0;
	while (i < n - 1)
	{
		if (s1_tmp[i] != s2_tmp[i])
			return (s1_tmp[i] - s2_tmp[i]);
		i++;
	}
	return (s1_tmp[i] - s2_tmp[i]);
}
