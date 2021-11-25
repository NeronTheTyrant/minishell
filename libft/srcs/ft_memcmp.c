/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:58:11 by mlebard           #+#    #+#             */
/*   Updated: 2020/12/03 19:55:40 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: compares n bytes of  array s1 and array s2
** return: difference between first differing byte of s1 and s2, 0 if n == 0
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = s1;
	str2 = s2;
	if (n == 0)
		return (0);
	while (i + 1 < n && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
