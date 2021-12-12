/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:03:35 by mlebard           #+#    #+#             */
/*   Updated: 2021/01/12 14:40:52 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_absd(double d)
{
	int64_t		sign;
	t_dbit		dbit;

	dbit.d = d;
	sign = dbit.i >> 63;
	if (sign == -1)
		dbit.i &= 0x7FFFFFFFFFFFFFFF;
	return (dbit.d);
}
