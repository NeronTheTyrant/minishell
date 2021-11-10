/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 23:58:59 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 21:24:30 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage; checks that base is valid. Checks for duplicate characters,
** forbidden characters like ' ', '-', '+' or whitespaces, or there being less
** than 2 characters.
** return: 0 if OK, 1 if KO
*/

int	ft_check_base(char *base, int base_len)
{
	int	i;
	int	j;

	i = -1;
	if (base_len <= 1)
		return (1);
	while (base[++i])
		if (base[i] == 43 || base[i] == 45 || (base[i] >= 9 && base[i] <= 13)
			|| base[i] == ' ')
			return (1);
	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
