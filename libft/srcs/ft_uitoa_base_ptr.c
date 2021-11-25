/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base_ptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:15:10 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 23:23:10 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getbasenbrlen(uintptr_t n, int base_len)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= base_len;
		i++;
	}
	return (i);
}

char	*ft_uitoa_base_ptr(uintptr_t n, char *base_to)
{
	int		i;
	int		base_len;
	char	*dest;

	base_len = ft_strlen(base_to);
	if (ft_check_base(base_to, base_len) == 1)
		return (NULL);
	i = ft_getbasenbrlen(n, base_len);
	dest = malloc(sizeof(*dest) * (i + 1));
	if (dest == NULL)
		return (NULL);
	dest[i--] = '\0';
	while (i > -1)
	{
		dest[i] = base_to[n % base_len];
		n /= base_len;
		i--;
	}
	return (dest);
}
