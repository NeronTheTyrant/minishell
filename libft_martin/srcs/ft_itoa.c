/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:11:42 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:57:34 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return: length of number "nbr". returns 1 if nbr = 0
*/

static int	ft_getnbrlen(int nbr)
{
	int			i;
	long int	n;

	i = 0;
	n = nbr;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
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
** usage: converts int "n" to malloc'd, null-terminated string
** return: malloc'd string conversion of int "n" if OK, NULL if KO
*/

char	*ft_itoa(int n)
{
	int			i;
	char		*s;
	long int	nb;

	i = ft_getnbrlen(n);
	nb = n;
	s = malloc(sizeof(*s) * (i + 1));
	if (s == NULL)
		return (NULL);
	s[i--] = '\0';
	if (nb < 0)
		nb *= -1;
	while (i > -1)
	{
		s[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	if (n < 0)
		s[0] = '-';
	return (s);
}
