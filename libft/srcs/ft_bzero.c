/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:10:28 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:53:58 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: sets NULL bytes in n bytes of s array. same as ft_memset(s, '\0').
** return: void
*/

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*m;

	i = 0;
	m = s;
	while (i < n)
	{
		m[i] = '\0';
		i++;
	}
}
