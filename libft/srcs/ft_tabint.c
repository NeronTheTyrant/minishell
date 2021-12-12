/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:36:35 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/28 05:38:24 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: searches for int n in *tab. If it finds it, returns the index where
** it was found. If not, returns -1
*/

int	ft_tabint(int *tab, int n, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (n == tab[i])
			return (i);
		i++;
	}
	return (-1);
}
