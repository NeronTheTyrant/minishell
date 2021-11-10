/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_abs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:11:42 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 21:50:52 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return: length of number "nbr". returns 1 if nbr = 0
*/

static int	ft_getnbrlen(intmax_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/*
** usage: converts absolute value of int "n" to malloc'd,
** null-terminated string.
** return: malloc'd string conversion of int "n" if OK, NULL if KO
*/

char	*ft_itoa_abs(intmax_t n)
{
	int			i;
	char		*s;

	i = ft_getnbrlen(n);
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
