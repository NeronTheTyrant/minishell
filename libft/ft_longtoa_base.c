/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_longtoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:58:45 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/12 00:28:50 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_tools.h"

char	*ft_longtoa_base(long nb, char *base)
{
	int		len;
	int		i;
	char	*str;

	len = ft_check_base(base);
	if (!len)
		return (NULL);
	i = ft_get_signed_nb_len(nb, len);
	str = (char *)malloc(sizeof(*str) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	str[0] = '-';
	if (!nb)
		str[0] = base[0];
	while (nb)
	{
		i--;
		str[i] = base[ft_abs(nb % len)];
		nb /= len;
	}
	return (str);
}
