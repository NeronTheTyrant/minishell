/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:36:26 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/11 21:10:30 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stddef.h>

int	ft_atoi_n(const char *str, size_t n)
{
	int		result;
	int		sign;
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	result = 0;
	while (j < n && ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		i++;
		j++;
	}
	return (result * sign);
}
