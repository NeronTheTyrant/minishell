/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctomb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:59:11 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 23:23:39 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wctomb(char *pmb, wchar_t wc)
{
	if (wc < 0x80)
	{
		pmb[0] = wc;
	}
	else if (wc < 0x800)
	{
		pmb[0] = (wc >> 6 & 0x1F) | 0xC0;
		pmb[1] = (wc & 0x3F) | 0x80;
	}
	else if (wc < 0x10000)
	{
		pmb[0] = (wc >> 12 & 0x0F) | 0xE0;
		pmb[1] = (wc >> 6 & 0x3F) | 0x80;
		pmb[2] = (wc & 0x3F) | 0x80;
	}
	else
	{
		pmb[0] = (wc >> 18 & 0x07) | 0xF0;
		pmb[1] = (wc >> 12 & 0x3F) | 0x80;
		pmb[2] = (wc >> 6 & 0x3F) | 0x80;
		pmb[3] = (wc & 0x3F) | 0x80;
	}
	return (ft_wclen(wc));
}
