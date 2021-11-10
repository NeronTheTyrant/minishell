/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:12:52 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 22:26:40 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	ft_atof(char *str)
{
	int		i;
	int		fract;
	double	result;

	i = 0;
	result = 0;
	fract = 0;
	while (ft_isdigit(*str) == 1 || *str == '.')
	{
		if (ft_isdigit(*str) == 1)
		{
			result = (result * 10) + (*str - 48);
			if (fract == 1)
				i--;
		}
		if (*str == '.')
		{
			if (fract == 1)
				return (0);
			fract = 1;
		}
		str++;
	}
	result = result * pow(10, i);
	return (result);
}
