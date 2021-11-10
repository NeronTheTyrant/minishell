/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:46:56 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/08 17:32:09 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memory.h"
#include "ft_print.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	*nbr;
	int		ret;

	nbr = ft_itoa(n);
	if (!nbr)
		return (-2);
	ret = ft_putstr_fd(nbr, fd);
	free(nbr);
	return (ret);
}
