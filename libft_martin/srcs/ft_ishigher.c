/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ishigher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 21:18:56 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:55:33 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return: returns whichever value is highest.
*/

int	ft_ishigher(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
