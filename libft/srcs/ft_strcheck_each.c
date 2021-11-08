/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcheck_each.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:57:43 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 23:13:13 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: checks ever character of string *str using function (*f).
** return: returns 1 if every call to (*f) returns 1. Otherwise, returns 0
*/

int	ft_strcheck_each(char *str, int (*f)(char c))
{
	while (*str != '\0')
	{
		if ((*f)(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}
