/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:11:42 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/14 17:52:45 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
