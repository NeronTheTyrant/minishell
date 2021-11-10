/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb_to_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 11:45:11 by mlebard           #+#    #+#             */
/*   Updated: 2021/02/26 11:48:37 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: returns value of alpha from int argb
*/

int	rgb_to_r(int argb)
{
	unsigned int	temp;

	temp = argb;
	return ((temp & (0xFF << 24)) >> 24);
}
