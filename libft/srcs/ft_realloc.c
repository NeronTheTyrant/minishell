/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:10:45 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 22:23:05 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t len, size_t newlen)
{
	void	*new;

	if (newlen == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
	{
		return (malloc(newlen));
	}
	else if (newlen <= len)
	{
		return (ptr);
	}
	else
	{
		new = malloc(newlen);
		if (new == NULL)
			return (NULL);
		ft_memcpy(new, ptr, len);
		free(ptr);
	}
	return (new);
}
