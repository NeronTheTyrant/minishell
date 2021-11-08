/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:59:31 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/28 05:38:33 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return: if c is uppercase letter, return lowercase equivalent
** Else returns c
*/

int	ft_tolower(char c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}
