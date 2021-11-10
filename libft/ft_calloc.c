/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:53:33 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/09 00:03:41 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*result;

	result = (char *)malloc(count * size);
	if (!result)
		return (NULL);
	ft_bzero(result, count * size);
	return ((void *)(result));
}
