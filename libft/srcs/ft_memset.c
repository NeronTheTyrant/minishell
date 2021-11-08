/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:59:19 by mlebard           #+#    #+#             */
/*   Updated: 2020/12/03 20:00:30 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: fills n bytes of array b with character c
** return: start of array b
*/

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*m;

	i = 0;
	m = b;
	while (i < n)
	{
		m[i] = c;
		i++;
	}
	return (b);
}
