/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strfill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:20:38 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/28 05:40:35 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: mallocs a string and fills it with str, and pads with char c if
** necessary. minlen is the minimum amount of characters in the new string.
*/

char	*strfill(char *str, int minlen, char c)
{
	int		i;
	char	*new;

	i = ft_strlen(str);
	if (minlen < i)
		minlen = i;
	new = malloc(sizeof(*new) * (minlen + 1));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, str, i);
	while (i < minlen)
	{
		new[i] = c;
		i++;
	}
	new[i] = '\0';
	return (new);
}
