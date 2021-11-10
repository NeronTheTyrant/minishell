/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:45:51 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/09 13:37:01 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_print.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	ret;

	ret = ft_putstr_fd(s, fd);
	if (ret < 0)
		return (-1);
	if (ft_putchar_fd('\n', fd) != 1)
		return (-1);
	return (ret + 1);
}
