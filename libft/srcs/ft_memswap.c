/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:43:50 by mlebard           #+#    #+#             */
/*   Updated: 2021/02/25 13:50:52 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: Swaps the contents of variables *a and *b. *temp is a temporary buffer
** of the same type as *a and *b provided by the user. All elements must be of
** size len.
*/

void	ft_memswap(void *a, void *b, void *temp, size_t len)
{
	ft_memcpy(temp, a, len);
	ft_memcpy(a, b, len);
	ft_memcpy(b, temp, len);
}
