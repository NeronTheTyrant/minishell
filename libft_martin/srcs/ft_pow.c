/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:05:42 by mlebard           #+#    #+#             */
/*   Updated: 2021/01/15 12:25:35 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double d, int power)
{
	int		neg;
	double	res;

	res = d;
	if (power == 0)
		return (1);
	if (power < 0)
	{
		neg = 1;
		power = -power;
	}
	while (power > 1)
	{
		res *= d;
		power--;
	}
	if (neg == 1)
		return (1 / res);
	else
		return (res);
}
