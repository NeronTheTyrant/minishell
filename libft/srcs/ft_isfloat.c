/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:39:10 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:55:23 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Usage: Checks if string *str is a string representation of a floating nb.
** Return: 1 if OK, 0 if KO
*/

int	ft_isfloat(char *str)
{
	int	fract;

	fract = 0;
	while (ft_isdigit(*str) || *str == '.')
	{
		if (*str == '.')
		{
			if (fract == 1)
				return (0);
			fract = 1;
		}
		str++;
	}
	if (*str == '\0')
		return (1);
	else
		return (0);
}
