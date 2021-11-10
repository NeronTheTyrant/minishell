/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:27:35 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:56:16 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Usage: checks whether null-terminated string *str represents a number.
** By number, we mean a string of only numeric characters (0-9) that can be
** preceded by a single '-' (minus) sign.
** Return: 1 if OK, 0 if KO
*/

int	ft_isnumber(char *str)
{
	if (*str == '-')
		str++;
	return (ft_strcheck_each(str, &ft_isdigit));
}
