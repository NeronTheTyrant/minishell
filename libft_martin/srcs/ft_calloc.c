/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:38:52 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:54:19 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: mallocs "count" objects of size "size"
** return: area that was malloc'd if OK, NULL if KO
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	temp = malloc(size * count);
	if (temp == NULL)
		return (NULL);
	ft_bzero(temp, size * count);
	return (temp);
}
