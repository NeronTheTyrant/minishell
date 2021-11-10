/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcslen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 21:12:55 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/28 05:39:02 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcslen(wchar_t *wcs)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (wcs[i])
	{
		if (wcs[i] < 0x80)
			j += 1;
		else if (wcs[i] < 0x800)
			j += 2;
		else if (wcs[i] < 0x10000)
			j += 3;
		else
			j += 4;
		i++;
	}
	return (j);
}
