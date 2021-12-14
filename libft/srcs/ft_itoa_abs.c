/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_abs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:11:42 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/14 17:53:22 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: converts absolute value of int "n" to malloc'd,
** null-terminated string.
** return: malloc'd string conversion of int "n" if OK, NULL if KO
*/

char	*ft_itoa_abs(intmax_t n)
{
	int			i;
	char		*s;

	i = ft_getnbrlen_us(n);
	s = malloc(sizeof(*s) * (i + 1));
	if (s == NULL)
		return (NULL);
	s[i--] = '\0';
	while (i > -1)
	{
		s[i] = ft_abs(n % 10) + 48;
		n /= 10;
		i--;
	}
	return (s);
}
