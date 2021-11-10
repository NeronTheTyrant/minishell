/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:31:45 by mlebard           #+#    #+#             */
/*   Updated: 2021/04/23 18:15:35 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: turns 4 ints each representing alpha, red, green and blue respectively
** into a formated color int
*/

int	make_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}
