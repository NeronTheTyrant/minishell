/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 21:21:01 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:55:44 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return: returns whichever value is lowest
*/

int	ft_islower(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
