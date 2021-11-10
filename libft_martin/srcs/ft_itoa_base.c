/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:15:10 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 21:53:58 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getbasenbrlen(int n, int base_len)
{
	int			i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		n /= base_len;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(int n, char *base_to)
{
	int			i;
	int			base_len;
	long int	nb;
	char		*dest;

	base_len = ft_strlen(base_to);
	nb = n;
	if (ft_check_base(base_to, base_len) == 1)
		return (NULL);
	i = ft_getbasenbrlen(n, base_len);
	dest = malloc(sizeof(*dest) * (i + 1));
	if (dest == NULL)
		return (NULL);
	dest[i--] = '\0';
	if (n < 0)
		nb *= -1;
	while (i > -1)
	{
		dest[i] = base_to[nb % base_len];
		nb /= base_len;
		i--;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}
